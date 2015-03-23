# 2048
2048 game C++

<p>To compile : Download SFML 2.2 : http://www.sfml-dev.org/download/sfml/2.2/index-fr.php
<br> extract and copy the repo SFML where you want.
</p><p>
add the path to your env : export LD_LIBRARY_PATH=where_you_copied_the_sfml_repos/lib
          <br> example : export LD_LIBRARY_PATH=/home/pierre/SFML/lib
</p>

*********************************************************************************************************************
in the makefile : put your path to SFML lib instead of what is written

... -L where_you_copied_the_sfml_repos/lib/ <br>
... -I where_you_copied_the_sfml_repos/include

	
*********************************************************************************************************************	

To start the Game : <br/>
	1. go to your 2048 repos  
	2. command : make
