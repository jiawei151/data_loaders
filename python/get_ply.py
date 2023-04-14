import trimesh
import numpy as np
def get_scale_mat(mesh_file):
    pcd = trimesh.load(mesh_file)
    vertices = pcd.vertices
    bbox_max = np.max(vertices, axis=0)
    bbox_min = np.min(vertices, axis=0)
    center = (bbox_max + bbox_min) * 0.5
    radius = np.linalg.norm(vertices - center, ord=2,axis=-1).max()
    scale_mat = np.diag([radius, radius, radius,1.0]).astype(np.float32)
    scale_mat[:3,3] = center
    # print(scale_mat)
    # scale_mat_test = np.zeros_like(scale_mat)
    # scale_mat_test[:] = scale_mat[:]
    # scale_mat_test[:,2] = -scale_mat[:,2]
    # print(scale_mat_test)
    # print(np.matmul(scale_mat,np.diag((1,1,-1,1))))
    # print(np.linalg.inv(np.matmul(np.diag((1,1,-1,1)),np.linalg.inv(scale_mat))))
    return scale_mat