#!/bin/bash
# http://nginx.org/en/linux_packages.html

set -e
OS=centos
OSRELEASE=7
cat <<EOF > /etc/yum.repos.d/nginx.repo
[nginx]
name=nginx repo
baseurl=http://nginx.org/packages/$OS/$OSRELEASE/\$basearch/
gpgcheck=0
enabled=1
EOF

yum install nginx
