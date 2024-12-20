import os
import numpy as np
from skimage import io, color, filters
from sklearn.preprocessing import StandardScaler
from scipy.io import loadmat
import time
import pickle

# Load images from the BSDS500 dataset
def load_bsds500_images(path, split="train"):
    image_dir = os.path.join(path, split)
    images = []
    filenames = []
    for filename in os.listdir(image_dir):
        if filename.endswith('.jpg'):
            img = io.imread(os.path.join(image_dir, filename))
            images.append(img)
            filenames.append(filename.split('.')[0])  # Keep filename for matching .mat
    return images, filenames

# Load ground truth edge annotations from .mat files
def load_bsds500_annotations(path, filenames, split="train"):
    anno_dir = os.path.join(path, f"{split}")
    annotations = []
    first = True
    for filename in filenames:
        mat_path = os.path.join(anno_dir, f"{filename}.mat")
        mat_data = loadmat(mat_path)
        edges = mat_data["groundTruth"][0, 0]["Boundaries"]
        edges_data = edges[0, 0]
        if first:
            print(edges_data.shape)
            first = False
        annotations.append(edges_data)
    return annotations

# Function to extract features (e.g., gradients)
def extract_features(image):
    gray = color.rgb2gray(image)
    gradient_magnitude = filters.sobel(gray)  # Sobel gradient magnitude
    return gradient_magnitude.flatten()

def prepare_data(images, annotations, sample_size_per_class=50):

    X = []
    y = []

    for img, anno in zip(images, annotations):
        img_features = extract_features(img)
        labels = anno.flatten().astype(int) 

        edge_indices = np.where(labels == 1)[0]
        non_edge_indices = np.where(labels == 0)[0]
        
        sampled_edge_indices = edge_indices
        sampled_non_edge_indices = np.random.choice(
            non_edge_indices, size=len(non_edge_indices)//20, replace=False
        )
        
        sampled_indices = np.hstack([sampled_edge_indices, sampled_non_edge_indices])

        X.extend(img_features[sampled_indices])
        y.extend(labels[sampled_indices])

    return np.array(X).reshape(-1, 1), np.array(y)



if __name__ == "__main__":
    # Paths to dataset
    start_time = time.time() 
    image_path = "BSDS500/data/images"
    annotation_path = "BSDS500/data/groundTruth"
    train_images, train_filenames = load_bsds500_images(image_path, "train")
    train_annotations = load_bsds500_annotations(annotation_path, train_filenames, "train")

    print(len(train_images))
    print(len(train_annotations))
    current_time = time.time()
    print(f"extracted data: {current_time-start_time}")

    X, y = prepare_data(train_images, train_annotations)
    current_time = time.time()
    print(f"prepared data: {current_time - start_time}")

    scaler = StandardScaler()
    X = scaler.fit_transform(X)
    current_time = time.time()
    print(f"transformed data: {current_time - start_time}")

    with open('X.pk1', 'wb') as file:
        pickle.dump(X, file)
    with open('y.pk1', 'wb') as file:
        pickle.dump(y, file)