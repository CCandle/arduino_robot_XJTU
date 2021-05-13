import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d
import matplotlib.animation as animation

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

def draw_line(ax, p1, p2):
    v = p2-p1
    x = []
    y = []
    z = []
    for i in range(0, 100):
        x.append(p1[0] + v[0] * i / 100)
        y.append(p1[1] + v[1] * i / 100)
        z.append(p1[2] + v[2] * i / 100)
    ax.plot3D(x, y, z)

def draw_points(ax, arr):
    return ax.scatter3D([p[0] for p in arr], [p[1] for p in arr], [p[2] for p in arr])
    

# structrual parameters
R_0 = 1         # radius of the sphere
r_0 = .5        # inner length of the tetrahedron points to center
M_f = 500       # fixed mass
M_s = 1000       # dynamic mass out of 4

fig = plt.figure()
ax = axes3d.Axes3D(fig)
ax.set_xlim3d(xmin=-1.3, xmax=1.3)
ax.set_ylim3d(ymin=-1.3, ymax=1.3)
ax.set_zlim3d(zmin=-1, zmax=1)

draw_sphere(ax, 1)

fix_points = np.array([
    np.array([0, 0, R_0]),
    np.array([2/3*2**.5*R_0, 0, -1/3*R_0]),
    np.array([-2**.5/3*R_0, 6**.5/3*R_0, -R_0/3]),
    np.array([-2**.5/3*R_0, -6**.5/3*R_0, -R_0/3])
    ])

draw_points(ax, fix_points)
ax.scatter3D([0], [0], [0], color='red')

for i in fix_points:
    draw_line(ax, np.array([0, 0, 0]), np.array(i))

len_each = [.4, .8, .4, .4]
dyn_points = [len_each[i] * fix_points[i] for i in range(0, 4)]

center_of_mass = (sum(dyn_points) * M_s) / (M_f + M_s*4)

pnts_ani = draw_points(ax, dyn_points)
cen_ani = ax.scatter3D(center_of_mass[0], center_of_mass[1], center_of_mass[2], color='cyan')

# animation scripts
def update_points():
    pass
ani = animation.FuncAnimation(fig, update_points, np.arange(0, 100), interval=100, blit=True)

plt.show()