import os

def get_filepaths(directory):
    file_paths = []

    for root, directories, files in os.walk(directory):
        for filename in files:
            filepath = os.path.join(root, filename)
            file_paths.append(filepath)

    return file_paths 
  
full_file_paths = get_filepaths("/home/artem/projects/itlab/dataset_for_train/faces/negatives/")
f = open('/home/artem/projects/itlab/itlab-vision-faces-detection/ItlabFaceDetector/imgs/neg.txt', 'w')

for name in full_file_paths:
	f.write(name + "\n")