#RareProb-C
# Requirements/Compatibility
   R language is necessary
   Java1.7 or higher is necessary
   Unix-like system is required           
   
# Source Code Description
  Rareprob-C contains the following file
   (1) A probabilistic method for identifying rare variants:   
        C++ codes: probrare.cpp global.cpp global.h  
        R codes: r/estimate.r r/initialX.r r/function.r r/P_value.r
  (2) Implementation of hidden Markov models (HMM):
        C codes: backward.c baum.c forward.c hmmrand.c hmmutil.c nrutil.c sequence.c verbi.c nrutil.h hmm.h
   (3) Filtering, interval and calculation of initial R vector 
        java codes: intervalR.jar
  (4) shell script file gathering the intervalR.jar and rareprob
       linux shell: rareprob-c.sh
    
# Data Format Requirement    
    The RareProb-C can process two kinds genotype file format:
    1. File with reference causal rare varients information and reference panel information
        1.1 genotype format ( necessary ):    
              -----------------           
              0000101001100010   
              0000100000100000A   
              0000001000100000A   
              0000100001000000A   
              0000000000000000C    
              0000000000000000C    
              0000000000100100C    
              -----------------
          The first line of the file represents reference causal rare varients information. 
          And character '1' represents this site is a causal rare varient site, 
          while character '0' represents this site is a noncausal rare varient site. 
          Rest of lines represents genotype of each individual. 
          And the 'A' and 'C' of the last character of every line represents the individual is a case or control. 

    2. File with reference causal rare varients information and reference panel information
        
        2.1 genotype format ( necessary ):
                -----------------
              0000100000100000A  
              0000001000100000A 
              0000100001000000A  
              0000000000000000C 
              0000000000000000C    
              0000000000100100C  
              ----------------- 
              each of lines represents genotype of each individual.
              And the 'A' and 'C' of the last character of every line represents the individual is a case or control. 
              
    
    
    
    
    
