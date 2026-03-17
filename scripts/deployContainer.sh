#Save current directory
current_dir="${PWD}"

# Set Script path
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
cd "$SCRIPT_DIR" || exit 1

echo "This script does not build the container before deploying it. Whatever the current docker image on the system will be deployed to the server"

echo Pushing container to Proxmox registry

podman image tag webappdevkit:latest 192.168.1.253:5000/webappdevkit:latest

podman image push 192.168.1.253:5000/webappdevkit:latest --tls-verify=false

echo Push complete.

echo Loading container image from Proxmox registry.

# run podman container, replace old server if needed, will need to mount volume.
export CONTAINER_NAME='webAppDevKitDev'
ssh myserver "podman run -p 80:80 -d --name $CONTAINER_NAME --replace 192.168.1.253:5000/webappdevkit:latest"

cd $current_dir