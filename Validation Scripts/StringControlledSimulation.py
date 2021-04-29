import numpy as np
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d.axes3d as axes3d

def axisEqual3D(ax):
    extents = np.array([getattr(ax, 'get_{}lim'.format(dim))() for dim in 'xyz'])
    sz = extents[:,1] - extents[:,0]
    centers = np.mean(extents, axis=1)
    maxsize = max(abs(sz))
    r = maxsize/2
    for ctr, dim in zip(centers, 'xyz'):
        getattr(ax, 'set_{}lim'.format(dim))(ctr - r, ctr + r)

def polar_to_orthogonal(rho, theta, phi):
    return (
        rho * np.sin(phi) * np.cos(theta),  # x
        rho * np.sin(phi) * np.sin(theta),  # y
        rho * np.cos(phi)                   # z
    )

def draw_sphere(ax, R):
    theta, phi = np.linspace(0, 2 * np.pi, 100), np.linspace(0, np.pi, 100)
    THETA, PHI = np.meshgrid(theta, phi)
    (X, Y, Z) = polar_to_orthogonal(R, THETA, PHI)
    ax.plot_surface(X, Y, Z, alpha=0.2)

# structrual parameters
R_0 = 1         # radius of the sphere
r_0 = .5        # inner length of the tetrahedron points to center

fig = plt.figure()
ax = axes3d.Axes3D(fig)
ax.set_xlim3d(xmin=-2, xmax=2)
ax.set_ylim3d(ymin=-2, ymax=2)
ax.set_zlim3d(zmin=-2, zmax=2)
axisEqual3D(ax)

draw_sphere(ax, 1)

fix_points = [(0,0,R_0), (2/3*2**.5*R_0,0,-1/3*R_0), (-2**.5/3*R_0,6**.5/3*R_0,-R_0/3), (-2**.5/3*R_0,-6**.5/3*R_0,-R_0/3)]

ax.scatter3D([p[0] for p in fix_points], [p[1] for p in fix_points], [p[2] for p in fix_points])

plt.show()