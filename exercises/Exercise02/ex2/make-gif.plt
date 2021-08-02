#!gnuplot -c

# argument parsing (ARGC does not include the script name)
if (ARGC < 3) {
    print 'Usage: ' . ARG0 . ' data.in data.out data.gif'
    exit status 1
}
point_file = ARG1
centroid_file = ARG2
gif_file = ARG3

# specify format of input and output files
set datafile separator whitespace
set terminal gif animate delay 20

# determine the size of the dataset
stats centroid_file using 1 name 'Iteration' nooutput
num_rows = int(Iteration_records)
num_iterations = int(Iteration_max)
num_centroids = int(num_rows / (num_iterations + 1))

# create the animated plot
set output gif_file
do for [iteration = 0 : num_iterations] {
    print sprintf('Animating Iteration %02d/%02d...', iteration, num_iterations)

    set title sprintf('K-Means Clusters (Iteration %02d)', iteration)

    start = num_centroids * iteration
    end = num_centroids * (iteration + 1) - 1
    plot point_file using 1:2 with point pointtype 1 pointsize 0.5 linewidth 1 linecolor rgb 'blue' notitle, \
        centroid_file using 2:3 every ::start::end with point pointtype 2 pointsize 2 linewidth 2 linecolor rgb 'red' notitle
}
