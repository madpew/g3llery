<?php
/*  g3llery
    a simple and responsive grid-based gallery
    
    http://github.com/madpew/g3llery
 */

function readIni(){
  global $title;
  global $storage;
  global $copyrightInformation;
  global $twitterHandle ;
  global $emailAddress;
  global $useThumbs;
  global $useLightbox;
  
  if (file_exists("g3llery.ini")){
    $ini_array = parse_ini_file("g3llery.ini");
    $title = getValueOrDefault("title", $ini_array, "unnamed g3llery");
    $storage = getValueOrDefault("storage", $ini_array, "store");
    $copyrightInformation = getValueOrDefault("copyrightInformation", $ini_array, "2013 SomeLazyG3lleryAdmin");
    $twitterHandle = getValueOrDefault("twitterHandle", $ini_array, "");
    $emailAddress = getValueOrDefault("emailAddress", $ini_array, "");
    $useThumbs = getValueOrDefault("useThumbs", $ini_array, false);
    $useLightbox = getValueOrDefault("useLightbox", $ini_array, false);
  }else{
    $title = "unnamed g3llery";
    $storage = "store";
    $copyrightInformation = "2013 SomeLazyG3lleryAdmin";
    $twitterHandle = "";
    $emailAddress = "";
    $useThumbs = false;
    $useLightbox = false;
  }
}

function getValueOrDefault($key, $array, $default){
  if (array_key_exists($key, $array)){
    return $array[$key];
  }
  return $default;
}

function createThumbnail($source, $target){
  $path = pathinfo($target, PATHINFO_DIRNAME); 
  
  if (!is_dir($path) && !file_exists($path)){
    if (!mkdir($path, 0777, true)){
      return false;
    }
  }
  
  $newSize = 512;
  list($width, $height) = getimagesize($source);
  $ext = mb_strtolower(pathinfo($source, PATHINFO_EXTENSION), 'UTF-8');
     
  if ($ext == "png"){
    $image = imagecreatefrompng($source);
  }
  
  if ($ext == "jpg" ||$ext == "jpeg"){
    $image = imagecreatefromjpeg($source);
  }
  
  if ($ext == "gif"){
    $image = imagecreatefromgif($source);
  }
  
  $image_p = imagecreatetruecolor($newSize, $newSize) or die('Could not create new image');
  imagecopyresampled($image_p, $image, 0, 0, 0, 0, $newSize, $newSize, $width, $height);

	imagejpeg($image_p, $target, 80);
	imagedestroy($image_p);
	
	return true;
}

function scandirSorted($path){
	$sortedData  = array();
	$data1       = array();
	$data2       = array();
	
	foreach(scandir($path) as $file){
		if(!strstr($path, '..')){
			if(is_file($path.$file)){
				array_push($data2, $file);
			}else{
				array_push($data1, $file);
			}
		}
	}
	
	$sortedData = array_merge($data1, $data2);
	return $sortedData;
}

function putBox($image, $text = "", $link = "", $class = ""){
	echo "<div class=\"box\">\n";
	echo "  <div class=\"boxInner";
	if ($class != "") echo " " . $class;
	echo "\">\n";
	echo "    ";
	if ($link != ""){
		echo "<a href=\"" . $link . "\">";
	}

	echo "<img src=\"" . $image . "\" alt=\"" . $text . "\" />";
	
	if ($link != ""){
		echo "</a>";
	}

	echo "\n";
	if ($text != "") echo "    <div class=\"titleBox\">" . $text . "</div>\n";
	echo "  </div>\n";
	echo "</div>\n";
}

function putImageBox($image, $text = "", $fullsize = ""){
  global $useLightbox;
  
  $big = $image;
  if ($fullsize != "") $big = $fullsize;
  
	echo "<div class=\"box\">\n";
	echo "  <div class=\"boxInner\">\n";
	echo "    ";
	echo "<a href=\"" . $big . "\"";
	
	if ($useLightbox){
	echo " data-lightbox=\"only\"";
	}
	
	if ($text != ""){
	echo " title=\"" . $text . "\"";
	}
	
	echo " >";
	echo "<img src=\"" . $image . "\" alt=\"" . $text . "\" /></a>";
	echo "\n";
	if ($text != "") echo "    <div class=\"titleBox\">" . $text . "</div>\n";
	echo "  </div>\n";
	echo "</div>\n";
}

function putTwitterBox(){
  global $twitterHandle;
  if ($twitterHandle != ""){
    putBox("img/twitter.png", $twitterHandle . " on twitter", "http://twitter.com/" . $twitterHandle, "twitter");
  }
}

function putEmailBox(){
  global $emailAddress;
  if ($emailAddress != ""){
    putBox("img/mail.png", $emailAddress, "mailto:" . $emailAddress, "email");
  }
}

function putBackBox(){
  putBox("img/back.png", "back to index", "?", "back");
}

function putErrorBox($msg){
  putBox("img/error.png", $msg, "", "error");
}

function putFolderBox($folder){
  global $storage;
  $image = "img/folder.png";
	$text = $folder;
	$link = "?id=" . $folder;
	
	if (file_exists($storage . "/" . $folder . "/logo.png")) $image = $storage . "/" . $folder . "/logo.png";
	if (file_exists($storage . "/" . $folder . "/logo.jpg")) $image = $storage . "/" . $folder . "/logo.jpg";
  if (file_exists($storage . "/" . $folder . "/title.txt")) $text = file_get_contents($storage . "/" . $folder . "/title.txt");
	putBox($image, $text, $link, "folder");
}

function putLogoBox($folder){
  global $storage;
  $image = "img/folder.png";
	$text = $folder;
	
	if (file_exists($storage . "/" . $folder . "/logo.png")) $image = $storage . "/" . $folder . "/logo.png";
	if (file_exists($storage . "/" . $folder . "/logo.jpg")) $image = $storage . "/" . $folder . "/logo.jpg";
  if (file_exists($storage . "/" . $folder . "/title.txt")) $text = file_get_contents($storage . "/" . $folder . "/title.txt");
  
	putBox($image, $text, "", "logo");
}

function g3lleryHeader(){
  global $title;
  global $useLightbox;
  
  echo "<title>" . $title . "</title>\n";
  echo "<link rel=\"stylesheet\" href=\"css/g3llery.css\" type=\"text/css\" />\n";
  
  if ($useLightbox){
    echo "<script src=\"js/jquery-1.10.2.min.js\"></script>\n";
    echo "<script src=\"js/lightbox-2.6.min.js\"></script>\n";
    echo "<link href=\"css/lightbox.css\" rel=\"stylesheet\" type=\"text/css\" />\n";
  }
}

function g3lleryFooter(){
  global $copyrightInformation;
  
  echo "<footer class=\"footer\">\n";
  if ($copyrightInformation != ""){
    echo "&copy; " . $copyrightInformation . "<br />\n";
  }
  echo "powered by <a href=\"http://github.com/madpew/g3llery\">g3llery</a>, ";
  echo " icons by <a href=\"http://lorcblog.blogspot.com\">Lorc</a> licensed under <a href=\"http://creativecommons.org/licenses/by/3.0/\">CC BY 3.0</a><br />\n";
  echo "</footer>\n";
}

function show404(){
  putErrorBox("Gallery Not Found");
	putBackBox();
}

function showIndex(){
  global $storage;

  if (file_exists("logo.png")){
    putBox("logo.png");
  }else if (file_exists("logo.jpg")){
    putBox("logo.jpg");
  }
    
  $currentdir = $storage . "/";
  $folder = array_diff(scandirSorted($currentdir), array('..', '.', 'Thumbs.db', 'thumbs.db', '.DS_Store', 'logo.png', 'logo.jpg', 'title.txt'));

  if (empty($folder)){
    putErrorBox("ERROR: folder '" . $storage . "' not found or empty.");
  }
    
	foreach($folder as $item){
    if (is_dir($currentdir . $item)){
      putFolderBox($item);
    }
	}

  putTwitterBox();
  putEmailBox();
}

function showGallery($reference){
  global $storage;
  global $useThumbs;
  
	$currentdir = $storage . "/" . $reference . "/";
	$thumbdir = "thumbs/" . $reference . "/";
	
	$folder = array_diff(scandirSorted($currentdir), array('..', '.', 'Thumbs.db', 'thumbs.db', '.DS_Store', 'logo.png', 'logo.jpg', 'title.txt'));

  putLogoBox($reference);

	foreach($folder as $item){
	  $ext = mb_strtolower(pathinfo($item, PATHINFO_EXTENSION), 'UTF-8');
    $filename = pathinfo($item, PATHINFO_FILENAME);
    
    if (($ext == "png") ||($ext == "jpg") ||($ext == "jpeg") ||($ext == "gif")){
      if ($useThumbs){
        $thumb = $thumbdir . $filename . ".jpg";
      
        if (!file_exists($thumb)){
          if (createThumbnail($currentdir . $item, $thumb)){
            putImageBox($thumb, $item, $currentdir . $item);
          }else{
            $useThumbs = false;
            putErrorBox("ERROR: thumbnail-directory '" . $thumb . "' not found or not writable");
          }
        }else{
          putImageBox($thumb, $item, $currentdir . $item);
        }
      }
      
      if (!$useThumbs){
        putImageBox($currentdir . $item, $item);
      }
    }
	}

  putTwitterBox();
  putEmailBox();
  putBackBox();
}

function g3lleryBody(){
  global $storage;

  if (isset($_GET['id'])){
    $reference = $_GET['id'];
    $tmpdir = $storage . "/" . $reference;
    clearstatcache();

    if (is_dir($tmpdir)){
      showGallery($reference);
    }else{
      show404();
    }
  }else{
    showIndex();
  }
}

readIni();

?>