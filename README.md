# C++ FastCGI template

## Prereq

Ubuntu 16.04:

```
sudo apt install nginx libfcgi libfcgi-dev spawn-fcgi
```

## nginx conf

```
location /myapi {
	fastcgi_pass unix:/var/run/mydaemon.sock;
	
	allow 127.0.0.1;
	allow ::1;
	deny all;

	fastcgi_param  SCRIPT_FILENAME    $document_root$fastcgi_script_name;
	fastcgi_param  QUERY_STRING       $query_string;
	fastcgi_param  REQUEST_METHOD     $request_method;
	fastcgi_param  CONTENT_TYPE       $content_type;
	fastcgi_param  CONTENT_LENGTH     $content_length;

	fastcgi_param  SCRIPT_NAME        $fastcgi_script_name;
	fastcgi_param  REQUEST_URI        $request_uri;
	fastcgi_param  DOCUMENT_URI       $document_uri;
	fastcgi_param  DOCUMENT_ROOT      $document_root;
	fastcgi_param  SERVER_PROTOCOL    $server_protocol;
	fastcgi_param  REQUEST_SCHEME     $scheme;
	fastcgi_param  HTTPS              $https if_not_empty;

	fastcgi_param  GATEWAY_INTERFACE  CGI/1.1;
	fastcgi_param  SERVER_SOFTWARE    nginx/$nginx_version;

	fastcgi_param  REMOTE_ADDR        $remote_addr;
	fastcgi_param  REMOTE_PORT        $remote_port;
	fastcgi_param  SERVER_ADDR        $server_addr;
	fastcgi_param  SERVER_PORT        $server_port;
	fastcgi_param  SERVER_NAME        $server_name;
}
```

## make

```
make
```

## install

```
sudo make install
sudo service mydaemon start
```

Automatically starts on next boot.

If you have already installed it, mydaemon is running, and just now made a slight change:


```
sudo make liveinstall
```

## run without installation

```
spawn-fcgi -P ~/mydaemon.pid -s ~/mydaemon.sock -M 0666 ./bin/mydaemon
```

## What you need to implement

see: [src/KVSHandler.h](./src/KVSHandler.h)  
modify: [src/mydaemon.cpp](./src/mydaemon.cpp).  
  
For KVSHandler usage: see [doc/simpletest.php](./doc/simpletest.php).  
  
sample benchmark: see [doc/benchmark_note.md](./doc/benchmark_note.md).