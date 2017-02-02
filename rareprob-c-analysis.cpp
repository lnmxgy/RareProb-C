#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
#include <string> 
#include <fstream>
#include <string.h>
using namespace std;

int readline(FILE *fp, char *s){
	int j;
	j=0;
	while(!feof(fp) && (s[j] = fgetc(fp)) != '\n') j++;
	s[j]='\0';
	if (j==0 && feof(fp)) return -1;
	else return j;    
}

int splitline(char *s, char term[][100]){
int j, k, n, slen;
	j=0; n = 0;
	slen = strlen(s);
	while (j < slen){
		while((s[j]==' ' || s[j]=='\t' || s[j]=='\r' || s[j]=='\n') && j<slen ) j++;
		k = 0;
		while((s[j]!=' ' && s[j]!='\t' && s[j]!='\r' && s[j]!='\n') && j<slen ) { term[n][k++] = s[j++]; }
		term[n][k]='\0';
		n++;
	}
	return n;    
}


	
/*-----------------------------------------------------------*/
int main(int argc,char *argv[]){
	char linestring[1000];
	char filename[50],newname[50];
	int  i,j,ln,n2,n1,k;
	char term[100][100];
	char ref[200],ref1[200];
	char cv[100][100];
	int label,outret;

	float specific;
	float type1error;
	float type2error;
	float sensitive;
	float s1,s2,s3,s4;
	int n11,n10,n01,n00,n;

	FILE * inf=fopen(argv[1],"r");//argv[1]="****statistic"
	FILE * outf=fopen("out1.txt","w");
	FILE * inf1;
	FILE * outf1=fopen("outref.txt","w");
	FILE * outf2;

	while(!feof(inf)) {	
		if(readline(inf,linestring)==-1) break;		
		splitline(linestring,term);
		if(strcmp(term[0],"filename:")==0)   {
			i=1;
			inf1=fopen(term[1],"r");
			cout<<term[1]<<endl;
			readline(inf1,ref);
			fprintf(outf1,"%s\n",ref);
			fclose(inf1);
		}
		if(i==5) fprintf(outf,"%s\n",linestring);
		i++;
	}

	fclose(inf);
	fclose(outf);
	fclose(outf1);

	inf=fopen("out1.txt","r");
	outf=fopen("out2.txt","w");//estimate site
	inf1=fopen("outref.txt","r");//causal site reference
	FILE *outend = fopen("outend.txt","w");//last result
	fprintf(outend,"sensitive\ttype1error\ttype2error\tspecific\tpower\n");
	s1=s2=s3=s4=0;
	k=0;
	while(!feof(inf)){
		if(readline(inf,linestring)<1) break;
        	for(i=0;i<101;i++){ref1[i]='0';}
		i=0;
		fscanf(inf1,"%s\n",&ref[i]);

		n1=splitline(linestring,cv);
		for(j=0;j<n1;j++){
			label=atoi(cv[j]);
			ref1[label-1]='1';
		}
		fprintf(outf,"%s\n",ref1);
		n11=n10=n01=n00=0;
		for(j=0;j<100;j++){
			if((ref[j]=='1')&&(ref[j]==ref1[j])){n11++; }
			if((ref[j]=='0') && (ref1[j]=='1')){n01++;}
			if((ref[j]=='1') && (ref1[j]=='0')){n10++;}
			if((ref[j]=='0') && (ref1[j]==ref[j])){n00++; }
			n=n11+n10+n01+n00;
		}
	
		sensitive=n11*1.0/(n11+n10);
		type1error=n10*1.0/(n11+n10);
		type2error=n01*1.0/(n01+n00);
		specific=n00*1.0/(n01+n00);
		fprintf(outend,"%f\t%f\t%f\t%f\n",sensitive,type1error,type2error,specific);

		s1+=sensitive;
		s2+=type1error;
		s3+=type2error;
		s4+=specific;
		k++;
		cout<<"k= "<<k<<endl;
	}
	s1=s1/100;
	s2=(s2-1)/100;
	s3=s3/100;
	s4=(s4-1)/100;
	fprintf(outend,"=======================================\naverage\n%f\t%f\t%f\t%f\t%f\n",s1,s2,s3,s4,(1-s3));

	fclose(inf);
	fclose(outf);
	fclose(outend);
	return 0;

}
