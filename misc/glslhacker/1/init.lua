winW, winH = gh_window.getsize(0)

local aspect = winW / winH
camera = gh_camera.create_persp(60, aspect, 1.0, 1000.0)
gh_camera.set_viewport(camera, 0, 0, winW, winH)
gh_camera.set_position(camera, 20, 20, 80)
gh_camera.set_lookat(camera, 0, 0, 0, 1)
gh_camera.setupvec(camera, 0, 1, 0, 0)

color_prog = gh_node.getid("color_prog")

grid = gh_utils.grid_create()
gh_utils.grid_set_geometry_params(grid, 100, 100, 20, 20)
gh_utils.grid_set_lines_color(grid, 0.7, 0.7, 0.7, 1.0)
gh_utils.grid_set_main_lines_color(grid, 1.0, 1.0, 0.0, 1.0)
gh_utils.grid_set_main_x_axis_color(grid, 1.0, 0.0, 0.0, 1.0)
gh_utils.grid_set_main_z_axis_color(grid, 0.0, 0.0, 1.0, 1.0)
local display_main_lines = 1
local display_lines = 1
gh_utils.grid_set_display_lines_options(grid, display_main_lines, display_lines)