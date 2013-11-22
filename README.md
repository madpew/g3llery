![g3llery](https://raw.github.com/madpew/g3llery/master/logo.png)
g3llery
=======
## a simple and responsive grid-based gallery ##

### demo: ###
You can see g3llery running here:
[http://pixelsiege.net/g3llery](http://pixelsiege.net/g3llery)

### installation instructions: ###

g3llery comes in 2 flavors: normal (lightbox2 included) and minimal (just g3llery, lightbox2 disabled)

1. download the according zip-archive and extract it to your webserver.

2. create a directory that will hold your galleries (default: "store")

3. edit g3llery.ini

4. (optional) if you want to use thumbnails (recommended) create a directory called "thumbs" and allow php write-access to that directory

5. create subdirectories in your store-directory and fill them with pictures (png, jpg, gif supported)

thumbnails (if enabled in g3llery.ini) will be generated when the gallery is viewed for the first time.

### further customizations: ###

- upload a logo.png (recommended size 512 x 512px) into your main g3llery-directory. It will show up on your index.
- upload a logo.png/logo.jpg into a gallery (recommended size 512 x 512px) to use it instead of the folder icon.
- upload a "title.txt" into a gallery to override that gallerys title with its content. 