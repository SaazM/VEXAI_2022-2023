def find_depth_average(tl, tr, bl, br, h, w, depths):
    new_height = h // 2
    new_width = w // 2    
    tl[0] += new_width // 2
    tl[1] += new_height // 2
    bl[1] -= new_height // 2
    tr[0] -= new_width // 2
    
    div = new_height * new_width
    
    sums = 0
    for i in range(tl[1], bl[1], 1):
        for j in range(tl[0], tr[0], 1):
            sums += depths[i][j]            
    sums /= div
    return(sums)

def find_depth_centerpoint(tl, tr, bl, br, h, w, depths):
    center_height = h // 2
    center_height += tl[1]
    
    center_width = w // 2
    center_width += tl[0]
    
    return(depths[center_height][center_width])

def find_depth_minimum(tl, tr, bl, br, h, w, depths):
    minimum = 10000000000000000000000000
    
    new_height = h // 2
    new_width = w // 2    
    tl[0] += new_width // 2
    tl[1] += new_height // 2
    bl[1] -= new_height // 2
    tr[0] -= new_width // 2
    
    for i in range(tl[1], bl[1], 1):
        for j in range(tl[0], tr[0], 1):
            depth_here = depths[i][j]
            if depth_here < minimum:
                minimum = depth_here
    return(minimum)
