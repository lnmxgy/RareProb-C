#!bin/bash

while getopts "i:sdntmx:hl" arg
do
	case $arg in
		#r) reference=$OPTARG;;
		i) input=$OPTARG;;
		s) sita=$OPTARG;;
		d) distance=$OPTARG;;
		n) iterationNum=$OPTARG;;
		t) delta=$OPTARG;;
		m) miu=$OPTARG;;
		x) isXExist=$OPTARG;;
		h) proThreshold=$OPTARG;;
		l) referencePanelNum=$OPTARG;;
		?) echo "unknown parameter";;
	esac
done

if [ ! -d $input ]
then 	
	echo $input "is not a dir"
	exit;
fi
#if [ ! -d $reference ]
#then 	
#	echo $reference "is not a dir"
#	exit;
#fi
make

dirname=$input
#echo $dirname

referencePrefix="./data/referencePanel";
#echo $referencePrefix

for file in `ls "$dirname" `

	do 
		echo "rareprob2: $file is processing......."
#		echo "1. filter begin"
		inputFileName=$file
		input="$dirname""/""$inputFileName"
		reference="$referencePrefix""/""$file"
		java -jar intervalR.jar -r $reference -i $input `if [ $sita ];then echo " -s $sita";fi` `if [ $distance];then echo " -d $distance";fi` `if [ $iterationNum];then echo " -n $iteravtionNum";fi` `if [ $delta ]; then echo " -t $delta"; fi ` `if [ $miu ]; then echo " -m $miu"; fi` `if [ $isXExist ]; then echo " -x $isXExist"; fi ` `if [ $proThreshold ]; then echo " -h $proThreshold"; fi ` `if [ $referencePanelNum ]; then echo " -l $referencePanelNum"; fi `
		filteredFile="./data/filtered/""${inputFileName}"
		siteInfo="./data/input_siteInfo/"$inputFileName".siteList"
	#	vafFile="./data/vaf/"
#		echo "2. initialR over"
		./rareprob  $filteredFile $siteInfo  1>>./data/result/90-0.05statistic
	
#		echo "3. rareprob2 over"

	done
echo "finished!"
