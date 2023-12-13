import xacro

import os
import sys
import xacro
import sdf2urdf
import json

def setup_json_start(root_path):
    # Initialize the JSON structure
    json_data = {
        "extract": [],
        "path": "",
        "robots": []
    }
    return json_data

def norm(base_path, relative_path):
    # Normalize the combined path
    combined_path = os.path.normpath(os.path.join(base_path, relative_path))
    # Remove the base path
    return os.path.relpath(combined_path, base_path)

def append_robot(json_data, full_base_path, name, urdf, meshInDir, outputDir):
    # Append a robot to the JSON structure

    robot_data = {
        "name": name,
        "urdf": norm(full_base_path, urdf),
        "meshInDir": norm(full_base_path, meshInDir),
        "outputDir": norm(full_base_path, outputDir)
    }
    json_data["robots"].append(robot_data)

def finalize_and_write_json(json_data, file_path):
    # Convert the dictionary to a JSON string and write it to a file
    with open(file_path, 'w') as file:
        json.dump(json_data, file, indent=4)

def process_xacro_file(input_file, output_file):
    # Backup the original sys.argv
    original_argv = sys.argv

    # Construct the argument list as it would be on the command line
    sys.argv = ['xacro', input_file, '-o', output_file]
    error = False
    try:
        # Call the main function of xacro
        xacro.main()
        print("Complete")
    except Exception as e:
        print(f"Error processing {input_file}: {e}")
        error = True
    finally:
        # Restore the original sys.argv
        sys.argv = original_argv
    return error

def process_sdf_file(input_file, output_file):
    # Backup the original sys.argv
    original_argv = sys.argv

    # Construct the argument list as it would be on the command line
    sys.argv = ['sdf2urdf', input_file, output_file]
    error = False
    try:
        # Call the main function of xacro
        sdf2urdf.main()
        print("Complete")
    except Exception as e:
        print(f"Error processing {input_file}: {e}")
        error = True
    finally:
        # Restore the original sys.argv
        sys.argv = original_argv
    return error

def main():
    total_manufacturers = 0
    total_manufacturers_errors = 0
    manufacturer_error_list = []

    total_models = 0
    total_model_errors = 0
    model_error_list = []

    base_dir = '../processed'  # Base directory where manufacturers' folders are located
    full_base_path = os.path.normpath(os.path.join(os.getcwd(), base_dir))
    json_robot_list = setup_json_start(full_base_path)

    for manufacturer in os.listdir(base_dir):
        manufacturer_path = os.path.join(base_dir, manufacturer)
        if manufacturer == ".idea" or manufacturer == "__pycache__" or manufacturer == "GazeboMaterial" or manufacturer != "ABB":
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
                            error = process_xacro_file(input_file, output_file)
                            if error:
                                total_model_errors += 1
                                model_error_list += [model_path]
                            else:
                                append_robot(json_robot_list, full_base_path, model, output_file, model_path, model_path)
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
                            error = process_sdf_file(input_file, output_file)
                            if error:
                                total_model_errors += 1
                                model_error_list += [model_path]
                            else:
                                append_robot(json_robot_list, full_base_path, model, output_file, model_path, model_path)
                        else:
                            print("{} not found!".format(input_file))
                            total_model_errors += 1
                            model_error_list += [model_path]

                    elif os.path.isfile(os.path.join(model_path, model + '.urdf')):
                        print("URDF already present - no processing needed")
                        output_file = os.path.join(model_path, model + '.urdf')
                        append_robot(json_robot_list, full_base_path, model, output_file, model_path, model_path)
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

    finalize_and_write_json(json_robot_list, os.path.join(base_dir, "robot_list.json"))

if __name__ == '__main__':
    main()
