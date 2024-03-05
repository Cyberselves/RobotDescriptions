import os

def rename_files(directory, prefix):
    """
    Renames all files in the specified directory by adding a prefix to their existing names.

    :param directory: Path to the directory containing the files.
    :param prefix: The string to be added before each file name.
    """
    # Check if the directory exists
    if not os.path.exists(directory):
        print(f"The directory '{directory}' does not exist.")
        return

    # Iterate over all files in the directory
    for filename in os.listdir(directory):
        # Construct the old and new file paths
        old_file = os.path.join(directory, filename)
        new_file = os.path.join(directory, prefix + filename)

        # Rename the file
        os.rename(old_file, new_file)
        print(f"Renamed '{filename}' to '{prefix + filename}'")

def main():
    # Rename all files in the current directory
    directory = "C:/Users/bajwa/Desktop/github_files/Isaac_Sim_Work/Sarcomere_Arms/urdf/arms_plus_hands/hands_meshes/right_hand/meshes/"
    rename_files(directory=directory, prefix="r_")

if __name__ == "__main__":
    main()

