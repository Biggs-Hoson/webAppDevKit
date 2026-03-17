#Save current directory
current_dir="${PWD}"

# Set Script path
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
cd "$SCRIPT_DIR" || exit 1

echo "This script does not build the container before deploying it. Whatever the current docker image on the system will be deployed to the server"

cd ../artefacts

if [ ! -f webappdevkit.tar ]; then
    podman save -o webappdevkit.tar webappdevkit:latest
fi

echo Transfering container image.
scp webappdevkit.tar myserver:containerImageImports
echo Transfer complete.


#echo Loading container image to local repository.
#ssh myserver "sudo podman load -i ./containerImageImports/webappdevkit.tar"

# run podman container 
#ssh myserver "sudo podman run -p 80:80 localhost/webappdevkit:latest"


cd $current_dir