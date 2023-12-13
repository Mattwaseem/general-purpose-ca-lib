import imageio.v2 as imageio
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
from io import BytesIO

# Function to read all iterations from a file
def read_all_iterations_from_file(filename):
    all_iterations = []
    current_grid = []
    with open(filename, 'r') as file:
        for line in file:
            if line.strip().startswith("Iteration"):
                if current_grid:
                    all_iterations.append(np.array(current_grid))
                    current_grid = []
                continue
            row = [int(x) for x in line.split()]
            current_grid.append(row)
        if current_grid:
            all_iterations.append(np.array(current_grid))
    return all_iterations

# Function to convert a grid to an image
def grid_to_image(grid, cmap):
    fig, ax = plt.subplots()
    ax.imshow(grid, cmap=cmap, interpolation='nearest')
    ax.axis('off')

    # Save the plot to a BytesIO object
    buf = BytesIO()
    plt.savefig(buf, format='png', bbox_inches='tight', pad_inches=0)
    buf.seek(0)
    image = imageio.imread(buf)
    buf.close()
    plt.close(fig)
    return image

# Function to create a GIF from all iterations
def create_gif(all_iterations, filename, cmap, desired_fps=60):  # Increase desired_fps for faster animation
    images = [grid_to_image(grid, cmap) for grid in all_iterations]
    imageio.mimsave(filename, images, duration=1000 / desired_fps, loop=0)  # Loop the GIF indefinitely

# Color map
cmap = ListedColormap(['yellow', 'blue'])  # Modify for your color scheme

# File names
file_names = [
 
    "2D_Periodic_Moore_totalistic.txt",
    "2D_Fixed_Moore_totalistic.txt",
    "2D_Periodic_Moore_parity.txt",
    "2D_Fixed_Moore_parity.txt",
    "2D_NoBoundary_Moore_paity.txt",
    "1D_Periodic_VN_parity.txt",
    "1D_Fixed_VN_parity.txt",
    "1D_NoBoundary_VN_parity.txt",
    "1D_Periodic_VN_totalistic.txt",
  
]

# Create and save GIFs
for file_name in file_names:
    all_iterations = read_all_iterations_from_file(file_name)
    gif_filename = f"{file_name.split('.')[0]}.gif"
    create_gif(all_iterations, gif_filename, cmap, desired_fps=1)
    print(f"Saved {gif_filename}")
