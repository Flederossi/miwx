# miwx
A micro web server for static content

> It is designed to be as small and fast as possible, but still able to handle all kinds of GET requests featuring html, css, js as well as any kind of text files. However, it cannot yet process images that well.

![Alt Text](https://github.com/Flederossi/chip-x/blob/main/img/logo.png)

## Usage
> You can use it in every folder containing code for a website by calling:
```
sudo miwx [port]
```

## Installation
### Linux:
> Compile and install miwx by using:
> ```
> make install
> ```
> Now miwx should be installed. To check, go to the templates folder and run:
> ```
> sudo miwx 80
> ```
> This will start the web server on port 80. If you now search for 'localhost' or '127.0.0.1' in your browser you should get the output:
> ```
> 127.0.0.1:29573 -> 127.0.0.1:80 | ./index.html
> 127.0.0.1:29574 -> 127.0.0.1:80 | ./style.css
> ```
> Also the example website should show up like this:
> ![Alt Text](https://github.com/Flederossi/chip-x/blob/main/img/logo.png)
> Now you can run miwx in every folder of your machine to make that the root folder of the web server.
