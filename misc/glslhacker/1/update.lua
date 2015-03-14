gh_camera.bind(camera)
gh_renderer.clear_color_depth_buffers(0.2, 0.2, 0.2, 1.0, 1.0)

gh_gpu_program.bind(color_prog)
gh_object.render(grid)
