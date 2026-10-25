import os
from download_input import fetch_input_data



def CMake_text(day):
    CMake_list_text = f"""add_executable(day{day:02} day{day:02}.cpp)

target_link_libraries(day{day:02} PRIVATE common) """
    return CMake_list_text


def setup(day):
    #make directory
    new_dir = project_path + f"/day{day:02}"
    if not os.path.exists(new_dir):
        os.makedirs(new_dir)
        print("directory does not exits, creates new dir")
    else:
        print("directory already exists!")
    cpp_file = project_path + f"/day{day:02}/day{day:02}.cpp"
    h_file = project_path + f"/day{day:02}/day{day:02}.h"
    Cmake_file = project_path + f"/day{day:02}/CMakeLists.txt"

    root_CMake_line_text = f"add_subdirectory(day{day:02})"

    #make cpp file
    make_cpp_file(cpp_file, day)

    #make h file
    make_h_file(h_file, day)

    #write CMakeLists for day
    make_CMake(CMake_text(day), Cmake_file)

    #edit root CMakeLists
    root_CMake_line(root_CMake_line_text, project_path + f"/CMakeLists.txt")

    #fetch input data from web
    fetch_input_data(day)

def root_CMake_line(line, path):
    print("writing new line to root CMakeLists.txt")
    with open(path, "r+") as CMake_file:
        for row in CMake_file:
            pass
        last_line = row
        if line == last_line:
            return
        CMake_file.write("\n")
        CMake_file.write(line)

def read_template(path, day):
    with open(path, "r") as file:
        content = file.read()
    return content.replace("?", f"{day:02}")

def make_cpp_file(path, day):
    template_path = "C:/Users/anblo/Documents/CodingProjects/AoC_Uni/Script/template/template_main_cpp.txt"
    text = read_template(template_path, day)

    print("creating cpp file")
    if os.path.exists(path):
        print("cpp file for day already exists. skipping....")
        return
    with open(path,"w") as cppFile:
        cppFile.write(text)

def make_h_file(path, day):
    template_path = "C:/Users/anblo/Documents/CodingProjects/AoC_Uni/Script/template/template_h.txt"
    text = read_template(template_path, day)

    print("creating .h file")
    if os.path.exists(path):
        print("h file for day already exists. skipping....")
        return
    with open(path, "w") as hFile:
        hFile.write(text)

def make_CMake(text, path):
    print("creating CMakeLists for the day")
    if os.path.exists(path):
        print("CMakelists file for day already exists. skipping....")
        return
    with open(path, "w") as CMakeFile:
        CMakeFile.write(text)

if __name__== "__main__":
    import sys
    argv = sys.argv
    argc = len(argv)


    #set new working dir
    project_path = "C:/Users/anblo/Documents/CodingProjects/AoC_Uni"
    os.chdir(project_path)
    print(project_path)

    error = False
    if argc > 1:
        if argv[1].lower() == "help":
            print(" specify day!")
            error = True
        if not error:
            day = int(argv[1])
            if day < 25 and day > 0:
                print(f"setting up day {day:02}")
                setup(day)
            else:
                print("day must be between 0 and 25")
    else:
        day = int(input("what day do you want to setup?: "))
        if day < 26 and day > 0:
            setup(day) 









