def area(Q,T):

    def area_of_triangle(T):
        x_coords = [coord[0] for coord in T]
        y_coords = [coord[1] for coord in T]

        n = len(T)
        area = 0

        for i in range(n - 1):
            area += x_coords[i] * y_coords[i + 1]
            area -= y_coords[i] * x_coords[i + 1]

        area += x_coords[n - 1] * y_coords[0]
        area -= y_coords[n - 1] * x_coords[0]

        return abs(area) / 2

    q_corners_inside_t = []
    def inside_corners_q(T, Q):
        area_T = area_of_triangle(T)

        for corner in Q:
            total_area_Q = 0
            total_area_Q += area_of_triangle([T[0], T[1], corner]) + area_of_triangle(
                [T[0], T[2], corner]) + area_of_triangle([T[1], T[2], corner])
            if abs(area_T - total_area_Q) < 0.000001:
                q_corners_inside_t.append(corner)
        return q_corners_inside_t

    inside_corners_q(T, Q)

    def area_of_quadrilateral(Q):
        n = len(Q)
        area = 0

        for i in range(n - 1):
            area += Q[i][0] * Q[i + 1][1] - Q[i][1] * Q[i + 1][0]

        area += Q[n - 1][0] * Q[0][1] - Q[n - 1][1] * Q[0][0]

        return abs(area) / 2

    t_corners_inside_q = []
    def inside_corners_t(Q, T):

        area_quad = area_of_quadrilateral(Q)

        for corner in T:
            total_area_T = 0
            total_area_T += area_of_triangle([Q[0], Q[1], corner]) + area_of_triangle(
                [Q[1], Q[2], corner]) + area_of_triangle([Q[2], Q[3], corner]) + area_of_triangle([Q[3], Q[0], corner])
            if abs(area_quad - total_area_T) < 0.000001:
                t_corners_inside_q.append(corner)

        return t_corners_inside_q

    inside_corners_t(Q, T)

    def dot_product(v1, v2):
        return v1[0] * v2[0] + v1[1] * v2[1]

    def subtract(v1, v2):
        return v1[0] - v2[0], v1[1] - v2[1]

    def intersection_points_within_shapes(Q, T):
        shape_intersection_points = []

        for i in range(len(Q)):
            q1, q2 = Q[i], Q[(i + 1) % len(Q)]
            for j in range(len(T)):
                t1, t2 = T[j], T[(j + 1) % len(T)]

                q1q2 = subtract(q2, q1)
                t1t2 = subtract(t2, t1)
                q1t1 = subtract(t1, q1)

                denominator = dot_product(q1q2, (-t1t2[1], t1t2[0]))
                if denominator != 0:
                    t = dot_product(q1t1, (-t1t2[1], t1t2[0])) / denominator
                    u = -dot_product(q1q2, (-q1t1[1], q1t1[0])) / denominator

                    if 0 <= t <= 1 and 0 <= u <= 1:
                        intersection_point = q1[0] + t * q1q2[0], q1[1] + t * q1q2[1]
                        shape_intersection_points.append(intersection_point)

        return shape_intersection_points

    shufled_area_coordinates = intersection_points_within_shapes(Q, T) + t_corners_inside_q + q_corners_inside_t

    if len(shufled_area_coordinates) == 0:
        return 0

    import math

    def calculate_angle(point, reference_point):
        x, y = point[0] - reference_point[0], point[1] - reference_point[1]
        return math.atan2(y, x)

    def find_centroid(points):
        num_points = len(points)
        if num_points < 1:
            return None
        x, y = zip(*points)
        centroid_x = sum(x) / num_points
        centroid_y = sum(y) / num_points
        return (centroid_x, centroid_y)

    def order_clockwise(coordinates):
        centroid = find_centroid(coordinates)
        if centroid is None:
            return None

        sorted_coordinates = sorted(
            coordinates,
            key=lambda point: (
                calculate_angle(point, centroid),
                -point[1],
            ),
            reverse=True,
        )
        return sorted_coordinates

    ordered_coordinates = order_clockwise(shufled_area_coordinates)

    ordered_x = [i[0] for i in ordered_coordinates]
    ordered_y = [i[1] for i in ordered_coordinates]

    def area_calculator(x_coordinates, y_coordinates):
        n = len(x_coordinates)
        if n != len(y_coordinates) or n < 3:
            return 0
        a_sum = 0
        b_sum = 0
        for i in range(n - 1):
            a_sum += x_coordinates[i] * y_coordinates[i + 1]
            b_sum += y_coordinates[i] * x_coordinates[i + 1]

        a_sum += x_coordinates[n - 1] * y_coordinates[0]
        b_sum += y_coordinates[n - 1] * x_coordinates[0]

        return 0.5 * abs(a_sum - b_sum)

    return area_calculator(ordered_x, ordered_y)





