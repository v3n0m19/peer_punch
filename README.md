 .S    S.     sSSs_sSSs    S.        sSSs          sSSs   .S    S.    .S_SSSs    sdSS_SSSSSSbs  
.SS    SS.   d%%SP~YS%%b   SS.      d%%SP         d%%SP  .SS    SS.  .SS~SSSSS   YSSS~S%SSSSSP  
S%S    S%S  d%S'     `S%b  S%S     d%S'          d%S'    S%S    S%S  S%S   SSSS       S%S       
S%S    S%S  S%S       S%S  S%S     S%S           S%S     S%S    S%S  S%S    S%S       S%S       
S%S SSSS%S  S&S       S&S  S&S     S&S           S&S     S%S SSSS%S  S%S SSSS%S       S&S       
S&S  SSS&S  S&S       S&S  S&S     S&S_Ss        S&S     S&S  SSS&S  S&S  SSS%S       S&S       
S&S    S&S  S&S       S&S  S&S     S&S~SP        S&S     S&S    S&S  S&S    S&S       S&S       
S&S    S&S  S&S       S&S  S&S     S&S           S&S     S&S    S&S  S&S    S&S       S&S       
S*S    S*S  S*b       d*S  S*b     S*b           S*b     S*S    S*S  S*S    S&S       S*S       
S*S    S*S  S*S.     .S*S  S*S.    S*S.          S*S.    S*S    S*S  S*S    S*S       S*S       
S*S    S*S   SSSbs_sdSSS    SSSbs   SSSbs         SSSbs  S*S    S*S  S*S    S*S       S*S       
SSS    S*S    YSSP~YSSY      YSSP    YSSP          YSSP  SSS    S*S  SSS    S*S       S*S       
       SP                                                       SP          SP        SP        
       Y                                                        Y           Y         Y         

Hole chat is a chat application based on the concept of UDP hole punching. It is cli based and work only with linux to limitations of thread creation and other stuff in windows. 

In order to use the application :

First clone the files to your desired location 

Then cd into the application's directory

Use the make command to compile the file and then run ./holechat

Make sure your public port is 60001 before continuing
Enter the reciever's public IP and port and start chatting

Currently the application has some issues (which I am aware of, others maybe there but to me they don't exist :) )like:
1. There is no scroll feature
2. There are some losses and out of order message delivery (This is an inherent problem UDP :( )
3. The messages aren't encrypted
4. The indentation of terminal changes after running the application 

I won't be working on this anymore but I am thinking of rewriting it in python along with (hopefully) integrating TCP hole punching as well.
