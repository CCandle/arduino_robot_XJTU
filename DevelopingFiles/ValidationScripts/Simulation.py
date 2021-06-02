import imageio
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d
import matplotlib.animation as animation

# calculation utils


def polar_to_orthogonal(rho, theta, phi):
    return np.array((
        rho * np.sin(phi) * np.cos(theta),  # x
        rho * np.sin(phi) * np.sin(theta),  # y
        rho * np.cos(phi)                   # z
    ))


def draw_sphere(ax, R):
    theta, phi = np.linspace(0, 2 * np.pi, 100), np.linspace(0, np.pi, 100)
    THETA, PHI = np.meshgrid(theta, phi)
    (X, Y, Z) = polar_to_orthogonal(R, THETA, PHI)
    ax.plot_surface(X, Y, Z, alpha=0.1)


def draw_line(ax, p1, p2, *args, **kwargs):
    v = p2-p1
    x = []
    y = []
    z = []
    for i in range(0, 100):
        x.append(p1[0] + v[0] * i / 100)
        y.append(p1[1] + v[1] * i / 100)
        z.append(p1[2] + v[2] * i / 100)
    ax.plot3D(x, y, z, *args, **kwargs)


def draw_points(ax, arr, *args, **kwargs):
    return ax.scatter3D([p[0] for p in arr], [p[1] for p in arr], [p[2] for p in arr], *args, **kwargs)


# structrual parameters
R_0 = 1                 # radius of the sphere
r_0 = .2                # logically fixed eccentricity
M_f = 500               # fixed mass
M_s = 1000              # dynamic mass out of 4
u_bound = .8            # mass block boundary
l_bound = .5

dir_vec = np.array([
    np.array([0, 0, R_0]),
    np.array([2/3*2**.5*R_0, 0, -1/3*R_0]),
    np.array([-2**.5/3*R_0, 6**.5/3*R_0, -R_0/3]),
    np.array([-2**.5/3*R_0, -6**.5/3*R_0, -R_0/3])
])

# %% algo section

# use dir_vec[1:4] as base vector
# Ax = B


def frac_pos_arr(theta, phi):
    pres = []
    for i in range(0, 4):
        dv = [dir_vec[j] for j in range(0, 4) if (i != j)]
        x = np.linalg.solve(
            np.matrix(dv).T, polar_to_orthogonal(r_0, theta, phi).T)
        mid = (u_bound + l_bound) / 2
        x = x.T + np.array([mid]*3)
        pres.append(np.array([x[j if (j < i) else j-1]
                              if (i != j) else mid for j in range(0, 4)]))
    return sum(pres) / 4

# %% base figure


def drw_base_figure():
    fig = plt.figure()
    ax = axes3d.Axes3D(fig)
    ax.set_xlim3d(xmin=-1.3, xmax=1.3)
    ax.set_ylim3d(ymin=-1.3, ymax=1.3)
    ax.set_zlim3d(zmin=-1, zmax=1)

    draw_sphere(ax, 1)

    draw_points(ax, dir_vec)
    ax.scatter3D([0], [0], [0], color='red')

    for i in dir_vec:
        draw_line(ax, np.array([0, 0, 0]), np.array(i), '--')

    for i in dir_vec:
        draw_line(ax, i * l_bound, i * u_bound, color='gray')
    return ax


# %% dynamic figure
for num in range(0, 100):
    len_each = frac_pos_arr(0, np.pi / 50 * num)

    dyn_points = [len_each[i] * dir_vec[i] for i in range(0, 4)]
    center_of_mass = sum(dyn_points)

    d_p_ani = []
    ax = drw_base_figure()
    for dyn_point in dyn_points:
        p, = ax.plot3D(dyn_point[0], dyn_point[1],
                       dyn_point[2], 'o', color='green')
        d_p_ani.append(p)
    c_p_ani, = ax.plot3D(
        center_of_mass[0], center_of_mass[1], center_of_mass[2], 'o', color='cyan')
    plt.savefig('./AnimOut/' + str(num) + '.jpg')
    plt.close('all')
    print('Saved frame ' + str(num))

# %% create gif

image_list = []
for num in range(0, 100):
    image_list.append(imageio.imread('./AnimOut/' + str(num) + '.jpg'))

imageio.mimsave('./Bad_Alg_Anim.gif', image_list, 'GIF', duration=0.03)

# %%
