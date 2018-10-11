#!/usr/bin/env bash

# A Bash script to build and install Bayeux Discovery Tour on Ubuntu Linux.

opwd=$(pwd)

function my_exit()
{
    local error_code=$1
    if [ "x${error_code}" = "x" ]; then
	error_code=0
    fi
    shift 1
    local error_msg="$@"
    if [ ${error_code} -ne 0 -a -n "${error_msg}" ]; then
	echo >&2 "[error] ${error_msg}"
    fi
    exit ${error_code}
}

function my_usage()
{
    cat<<EOF

Options:

   --help               : print help
   --debug              : activate debug mode
   --dry-run            : dry run
   --only-configure     : perform configuration stage only

EOF
    return
}

dry_run=False
rebuild=0
only_configure=0
debug=0
bayeux_install_dir=""
bayeux_cmake_dir=""
bayeux_version=""
bxtour_source_dir="${opwd}"
bxtour_version="develop"
install_base_dir=$(pwd)/_install.d
build_base_dir=$(pwd)/_build.d

function cl_parse()
{
    while [ -n "$1" ]; do
	local arg="$1"
	if [ "${arg}" = "--help" ]; then
	    my_usage
	    my_exit 0
	elif [ "${arg}" = "--debug" ]; then
	    debug=1
	elif [ "${arg}" = "--dry-run" ]; then
	    dry_run=True
	elif [ "${arg}" = "--rebuild" ]; then
	    rebuild=1
	elif [ "${arg}" = "--only-configure" ]; then
	    only_configure=1
	fi
	shift 1
    done
    return 0
}

# Check Linuxbrew:
which brew > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo >&2 "[error] Linuxbrew is not setup! Please run linuxbrew_setup! Abort!"
    my_exit 1
else
    echo >&2 "[info] Found Linuxbrew : $(which brew)"
fi

# Check Bayeux:
which bxquery 1> /dev/null 2>&1
if [ $? -ne 0 ]; then
    my_exit 1 "Cannot find bxquery! Check your Bayeux setup!"
fi

bayeux_install_dir="$(bxquery --prefix)"
bayeux_cmake_dir="$(bxquery --cmakedir)"
bayeux_version="$(bxquery --version)"

echo >&2 "[info] Bayeux install dir : '${bayeux_install_dir}'"
echo >&2 "[info] Bayeux install dir : '${bayeux_cmake_dir}'"
echo >&2 "[info] Bayeux version     : '${bayeux_version}'"
echo >&2 "[info] BxTour source dir  : '${bxtour_source_dir}'"
echo >&2 "[info] BxTour version     : '${bxtour_version}'"
###my_exit 1

cl_parse $@
if [ $? -ne 0 ]; then
    echo >&2 "[error] Command line parsing failed!"
    my_exit 1
fi

# Check distribution:
distrib_id=$(cat /etc/lsb-release | grep DISTRIB_ID | cut -d= -f2)
distrib_release=$(cat /etc/lsb-release | grep DISTRIB_RELEASE | cut -d= -f2)
if [ "${distrib_id}" != "Ubuntu" ]; then
    echo >&2 "[error] Not an Ubuntu Linux!"
    my_exit 1
fi
if [ "${distrib_release}" != "16.04" -a "${distrib_release}" != "18.04" ]; then
    echo >&2 "[error] Not an Ubuntu Linux version 16.04 or 18.04! Abort!"
    my_exit 1
else
    echo >&2 "[info] Found Ubuntu Linux ${distrib_release}"
fi

# # Check Git source repository:
# echo >&2 "[info] BxTour source directory: '${bxtour_source_dir}'"
# ls -l ${bxtour_source_dir}/.git
# if [ ! -d ${bxtour_source_dir}/.git ]; then
#     echo >&2 "[error] Not the BxTour source directory."
#     app_exit 1
# fi
# bxtour_branch=$(git --git-dir=${bxtour_source_dir}/.git --work-tree=${bxtour_source_dir} branch | grep \* | tr -d [[:space:]\*] )
# echo >&2 "[info] BxTour Git branch: '${bxtour_branch}'"
# bxtour_version=${bxtour_branch}

install_dir=${install_base_dir}/${bxtour_version}
build_dir=${build_base_dir}/${bxtour_version}


if [ ! -d ${bxtour_source_dir} ]; then
    echo >&2 "[error] BxTour source directory '${bxtour_source_dir}' does not exist! Abort!"
    my_exit 1
fi

if [ -d ${install_dir} ]; then
    rm -fr ${install_dir}
fi

if [ ! -d ${build_dir} ]; then
    mkdir -p ${build_dir}
else
    if [ ${rebuild} -eq 1 ]; then
	echo >&2 "[info] Rebuilding BxTour..."
	rm -fr ${build_dir}
	mkdir -p ${build_dir}
    fi
fi

linuxbrew_prefix=$(brew --prefix)
echo >&2 "[info] Linuxbrew prefix : '${linuxbrew_prefix}'"

if [ ${dry_run} = True ]; then
      my_exit 0
fi

cd ${build_dir}
echo >&2 ""
echo >&2 "[info] Configuring..."
cmake \
    -DCMAKE_BUILD_TYPE:STRING="Release" \
    -DCMAKE_INSTALL_PREFIX:PATH="${install_dir}" \
    -DCMAKE_PREFIX_PATH:PATH="${linuxbrew_prefix}" \
    -DBayeux_DIR=${bayeux_cmake_dir} \
    -GNinja \
    ${bxtour_source_dir}
if [ $? -ne 0 ]; then
    echo >&2 "[error] BxTour ${bxtour_version} configuration failed!"
    my_exit 1
fi

if [ ${only_configure} -eq 0 ]; then

    echo >&2 ""
    echo >&2 "[info] Building..."
    ninja -j4
    if [ $? -ne 0 ]; then
	echo >&2 "[error] BxTour ${bxtour_version} build failed!"
	my_exit 1
    fi

    # echo >&2 ""
    # echo >&2 "[info] Testing..."
    # ninja test
    # if [ $? -ne 0 ]; then
    # 	echo >&2 "[error] BxTour ${bxtour_version} testing failed!"
    # 	my_exit 1
    # fi

    echo >&2 ""
    echo >&2 "[info] Installing..."
    ninja install
    if [ $? -ne 0 ]; then
	echo >&2 "[error] BxTour ${bxtour_version} installation failed!"
	my_exit 1
    fi
    tree ${install_base_dir}
fi

my_exit 0

# end
