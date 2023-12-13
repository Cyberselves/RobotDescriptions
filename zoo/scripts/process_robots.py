import xacro

import os
import sys
import xacro
import sdf2urdf

def process_xacro_file(input_file, output_file):
    # Backup the original sys.argv
    original_argv = sys.argv

    # Construct the argument list as it would be on the command line
    sys.argv = ['xacro', input_file, '-o', output_file]

    try:
        # Call the main function of xacro
        xacro.main()
        print("Complete")
    except Exception as e:
        print(f"Error processing {input_file}: {e}")
    finally:
        # Restore the original sys.argv
        sys.argv = original_argv

def process_sdf_file(input_file, output_file):
    # Backup the original sys.argv
    original_argv = sys.argv

    # Construct the argument list as it would be on the command line
    sys.argv = ['sdf2urdf', input_file, output_file]

    try:
        # Call the main function of xacro
        sdf2urdf.main()
        print("Complete")
    except Exception as e:
        print(f"Error processing {input_file}: {e}")
    finally:
        # Restore the original sys.argv
        sys.argv = original_argv

def main():
    total_manufacturers = 0
    total_manufacturers_errors = 0
    manufacturer_error_list = []

    total_models = 0
    total_model_errors = 0
    model_error_list = []

    base_dir = '../processed'  # Base directory where manufacturers' folders are located

    for manufacturer in os.listdir(base_dir):
        manufacturer_path = os.path.join(base_dir, manufacturer)
        if manufacturer == ".idea" or manufacturer == "__pycache__" or manufacturer == "GazeboMaterial":
            continue
        total_manufacturers += 1

        # Check if it's a directory
        if os.path.isdir(manufacturer_path):
            for modelname in os.listdir(manufacturer_path):
                model_path = os.path.join(manufacturer_path, modelname)
                print("Processing {} {}".format(manufacturer, modelname))
                # Check if it's a directory and contains a 'xacro' subdirectory
                model = modelname.lower()
                model = model.replace(' ', '_')
                total_models += 1
                if os.path.isdir(model_path):
                    if 'xacro' in os.listdir(model_path):
                        print("Found xacro - processing into urdf")
                        xacro_path = os.path.join(model_path, 'xacro')
                        input_file = os.path.join(xacro_path, model + '.xacro')
                        output_file = os.path.join(model_path, model + '.urdf')

                        # Process the xacro file
                        if os.path.isfile(input_file):
                            print("Running 'python .\\xacro.py {} -o {}'".format(input_file, output_file))
                            process_xacro_file(input_file, output_file)
                        else:
                            print("{} not found!".format(input_file))
                            total_model_errors += 1
                            model_error_list += [model_path]

                    elif os.path.isfile(os.path.join(model_path, model + '.sdf')):
                        print("Found sdf - processing into urdf")
                        input_file = os.path.join(model_path, model + '.sdf')
                        output_file = os.path.join(model_path, model + '.urdf')
                        if os.path.isfile(input_file):
                            print("Running 'python .\\sdf2urdf.py {} {}'".format(input_file, output_file))
                            process_sdf_file(input_file, output_file)
                        else:
                            print("{} not found!".format(input_file))
                            total_model_errors += 1
                            model_error_list += [model_path]

                    elif os.path.isfile(os.path.join(model_path, model + '.urdf')):
                        print("URDF already present - no processing needed")
                    else:
                        print("Unhandled exception")
                        total_model_errors += 1
                        model_error_list += [model_path]

                print("------------------------------------------------------------\n")
            print("***************All {} Models Processed***************\n\n".format(manufacturer))
        else:
            total_manufacturers_errors += 1
            manufacturer_error_list += [manufacturer]

    print("Successfully processed {}/{} manufacturers".format(
        total_manufacturers-total_manufacturers_errors, total_manufacturers))
    print("Problematic manufacturers: {}".format(manufacturer_error_list))

    print("Successfully processed {}/{} models".format(
        total_models - total_model_errors, total_models))
    print("Problematic models: {}".format(model_error_list))


if __name__ == '__main__':
    main()
