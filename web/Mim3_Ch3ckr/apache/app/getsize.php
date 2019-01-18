<?php
//error_reporting(-1);
//ini_set('display_errors', 'On');

class CurlClass{
    public function httpGet($url) {
    $ch = curl_init();  
 
    curl_setopt($ch,CURLOPT_URL,$url);
    curl_setopt($ch,CURLOPT_RETURNTRANSFER,true);
//  curl_setopt($ch,CURLOPT_HEADER, false); 
 
    $output=curl_exec($ch);
 
    curl_close($ch);
    return $output;
 }
}


class MainClass {

	public function __destruct() {
        $this->why =new CurlClass;
        echo $this->url;
        echo $this->why->httpGet($this->url);
	}
}


// Check if image file is a actual image or fake image
if(isset($_POST["submit"])) {
    $check = getimagesize($_POST['name']);
    if($check !== false) {
        echo "File is an image - " . $check["mime"] . ".";
        $uploadOk = 1;
    } else {
        echo "File is not an image.";
        $uploadOk = 0;
    }
}


?>




