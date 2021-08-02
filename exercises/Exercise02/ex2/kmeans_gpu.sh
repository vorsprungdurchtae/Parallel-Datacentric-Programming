#!/usr/bin/env zsh

### Job name
#SBATCH --job-name=kmeans
#SBATCH --account=lect0053

### File / path where STDOUT will be written, the %j is the job id
#SBATCH --output=output_%j.txt

### Optional: Send mail when job has finished
###SBATCH --mail-type=END
###SBATCH --mail-user=<email-address>

### Request time and memory
#SBATCH --time=00:10:00
#SBATCH --mem-per-cpu=1500

### Set Queue
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=24
#SBATCH --gres=gpu:volta:1

### Adapt to your directory
cd ~/ex2
./kmeans.exe ./input/large.in 1000000 5000 50

