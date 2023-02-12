<?php
$myfile1 = fopen("./files/1-Original-Raw-Data.txt", "r") or die("Unable to open file!");

$myfile2 = fopen("./files/2-Necessary-Data.txt", "w") or die("Unable to open file!");

// Output one character until end-of-file
$txt = 1;

while(!feof($myfile1)) {
  $txt = fgetc($myfile1);
  if(feof($myfile1)){
  	   		break;
  }
  if($txt == "]"){				//Stopping at Symptons ]
  	fwrite($myfile2, $txt);		//Writing ]
  	$txt = fgetc($myfile1);		//Getting comma
  	if(feof($myfile1)){
  	   		break;
  	}
  	fwrite($myfile2, $txt);		//Writing comma
  	   $txt =fgetc($myfile1);	//Getting other values
  	   if(feof($myfile1)){
  	   		break;
  	   }
  	   while($txt != "]" or feof($myfile1)){		//Skipping until ] found of common tests and procedures
  	   	$txt =fgetc($myfile1);
  	   }						//Found
  	   while($txt != "[" or feof($myfile1)){
  	   	$txt =fgetc($myfile1);
  	   }						//Opening of Medications [ Found
  	   fwrite($myfile2, $txt);	//Writing [ of Medications
  	   while($txt != "]" or feof($myfile1)){		//Loop till Closing ] of Medications
  	   $txt =fgetc($myfile1);	//Writing Medications
  	   fwrite($myfile2, $txt);
  	   }						//Found ]
  	   $txt = fgetc($myfile1);
  	   if(feof($myfile1)){
  	   		break;
  	   }
  	   while(1){
  	   	if(feof($myfile1)){
  	   		break;
  	   	}
  	   	if($txt == "\""){
  	   		$txt = fgetc($myfile1);
  	   		$var1 = ord($txt);
  	   		if($var1 >= 48 && $var1 <=57){
  	   			break;
  	   		}
  	   	}
  	   	$txt = fgetc($myfile1);
  	   	if(feof($myfile1)){
  	   		break;
  	   	}
  	   }
  	   $msg0 = "-";
  	   fwrite($myfile2, $msg0);
  	   $msg1 = "\"";
  	   fwrite($myfile2, $msg1);
  	   fwrite($myfile2, $txt);
  	continue;
  }
  fwrite($myfile2, $txt);
  if(feof($myfile1)){
  	   		break;
  	   	}
}

fclose($myfile1);
fclose($myfile2);

?>

