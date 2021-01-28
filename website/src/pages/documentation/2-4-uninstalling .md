# Uninstalling 

You can uninstall AppScope by simply deleting the code:  

```
rm -rf appscope
```

… and the associated history directory:

```
cd ~
rm -rf ./scope
```

Applications currently scope’d will continue to run. To remove the AppScope library from a running process, you will need to restart that process.