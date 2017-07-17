#!/bin/bash
#
# SCRIPT: build 
# AUTHOR: Tang Cheng
# DATE:   2017/07/17
# REV:    1.0.D (Valid are A, B, D, T, Q, and P)
#               (For Alpha, Beta, Dev, Test, QA, and Production)
#
# PLATFORM: Linux
#
# PURPOSE: Build a project managed with autoconf toolset.
# 
#
# set -n   # Uncomment to check script syntax, without execution.
#          # NOTE: Do not forget to put the # comment back in or
#          #       the shell script will never execute!
# set -x   # Uncomment to debug this shell script
#
##########################################################
#         DEFINE FILES AND VARIABLES HERE
##########################################################

this_script=$(basename $0)
top_dir=$(dirname $0)"/../../"
echo -e "$top_dir"
build_dir=build
enable_tests=false

##########################################################
#              DEFINE FUNCTIONS HERE
##########################################################

function usage
{
	echo -e "\nUsage: $this_script [enable-tests]"
	echo -e "\tenable-tests:    enable run tests base cpputest."
	exit 0
}

##########################################################
#               BEGINNING OF MAIN
##########################################################

case $# in
    0)
        enable_tests=true
	;;
    1)
        enable_tests=$1
	;;
    *)
        usage
	;;
esac

pushd $topdir

app_name=$(basename $(pwd))
docker_image_id=`echo "local/${app_name}:latest" | tr "[:upper:]" "[:lower:]"`
docker build -t $docker_image_id -f dockers/fedora25-x86_64-Dockerfile .

mkdir -p $build_dir
rm -fr $build_dir/*

if [ x"$enable_tests" = xtrue ]; then
    docker run -i -e DOCKER_HOST_USERID="$(id -u):$(id -g)" -e VERBOSE=1 -v $(pwd)/$build_dir:/root/project/$app_name/$build_dir --rm $docker_image_id /bin/bash << "EOF"
set -o errexit -o nounset \
\
&& autoreconf -i \
&& cd build \
&& ../configure --enable-tests \
&& make \
&& make check \
\
&& cd .. \
&& chown -R $DOCKER_HOST_USERID build
EOF
else
    docker run -i -e DOCKER_HOST_USERID="$(id -u):$(id -g)" -e VERBOSE=1 -v $(pwd)/$build_dir:/root/project/$app_name/$build_dir --rm $docker_image_id /bin/bash << "EOF"
set -o errexit -o nounset \
\
&& autoreconf -i \
&& cd build \
&& ../configure --enable-tests \
&& make \
\
&& cd .. \
&& chown -R $DOCKER_HOST_USERID build
EOF
fi

#popd

# End of script
