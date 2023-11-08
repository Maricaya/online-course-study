https://zhuanlan.zhihu.com/p/502375486

# 运行
```bash
docker container run -it -v /Users/xuluchu/Desktop/new-study/csapp-cmu213:/csapp-cmu213 --name=csapp_env centos /bin/bash
```

解决Failed to download metadata for repo ‘AppStream’ [CentOS]错误
```bash
cd /etc/yum.repos.d/
sed -i 's/mirrorlist/#mirrorlist/g' /etc/yum.repos.d/CentOS-*
sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*
yum update -y
```


