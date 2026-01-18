#Save current directory
current_dir="${PWD}"

# Set Script path
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
cd "$SCRIPT_DIR" || exit 1

cd ../backEnd

# Any other files need to be copied across to containerRootFiles here

# Build docker image
docker build -t webappdevkit -f ./docker/DockerFile --progress=plain ./ 

cd $current_dir