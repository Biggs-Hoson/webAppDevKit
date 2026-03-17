#Save current directory
current_dir="${PWD}"

# Set Script path
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
cd "$SCRIPT_DIR" || exit 1

cd ../backEnd

if [ -f ../artefacts/webappdevkit.tar ]; then
    rm ../artefacts/webappdevkit.tar
fi

# Build docker image
podman build -t webappdevkit -f ./docker/DockerFile --net=host --progress=plain ./ 

cd $current_dir