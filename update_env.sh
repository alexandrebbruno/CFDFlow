#run with source update_env.sh
#!/bin/bash
conda deactivate
conda env update --file environment.yml  --prune
conda activate cfdflow