#Save current directory
current_dir="${PWD}"

# Set Script path
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
cd "$SCRIPT_DIR" || exit 1

echo "This script does not build the container before testing it. Whatever the current docker image on the system will be run locally"

export CONTAINER_NAME='webAppDevKitDev'
podman run -it --rm -p 80:80 --name $CONTAINER_NAME --replace webappdevkit

cd $current_dir