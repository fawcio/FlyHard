#!/bin/bash

BUILD_TYPE="debug"
BUILD_TYPE_CMAKE=""
BUILD_DIRECTORY="./build"

usage()
{
  echo ""
  echo "Usage $0 [--build-type=debug/release] BUILD_BASEDIR"
  echo "This script creates/configures build directory for the Eclipse CDT4 project."
  echo ""
  echo "Parameters:"
  echo "--help        Print this help message."
  echo "--build-type  Sets the CMAKE_BUILD_TYPE variable (default: debug)."
}

# Command Line Options
while [ "${1:0:1}" == "-" ]; do
  case "$1" in
    --build-type=*)
      BUILD_TYPE=${1##--build-type=}
      shift
      ;;
    -*)
      echo "Error: Invalid option '$1'."
      usage
      exit 1
      ;;
    *)
      ;;
  esac
done

#Buidld type
case "$BUILD_TYPE" in
  debug)
    BUILD_TYPE_CMAKE="Debug"
    ;;
  release)
    BUILD_TYPE_CMAKE="Release"
    ;;
  *)
    echo "Error: Build type '${BUILD_TYPE}' not supported."
    usage
    exit 1
    ;;
esac

#Build directory
if [ "$1" == "" ]; then
  echo "Error: Please specify build directory to be used."
  usage
  exit 1
fi
BUILD_DIRECTORY="$1/SFGame-$BUILD_TYPE_CMAKE"
SOURCE_DIRECTORY=`pwd`
mkdir -p $BUILD_DIRECTORY
cd $BUILD_DIRECTORY

echo " Calling cmake ..."
echo "cmake -G \"Eclipse CDT4 - Unix Makefiles\" -D CMAKE_BUILD_TYPE='$BUILD_TYPE_CMAKE $BUILD_DIRECTORY'"
cmake -G "Eclipse CDT4 - Unix Makefiles" -D CMAKE_ECLIPSE_VERSION=4.6 -D CMAKE_BUILD_TYPE=$BUILD_TYPE_CMAKE $BUILD_DIRECTORY $SOURCE_DIRECTORY

cd -
