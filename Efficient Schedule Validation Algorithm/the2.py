def check_month(month_calendar):
    cost = []
    error = []
    m_indexes = [index for index, number in enumerate(month_calendar) if number == "m"]
    remainders_m = [num % 5 for num in m_indexes]
    unique_remainders_m = set(remainders_m)
    if len(unique_remainders_m) == 1:
        cost_of_mom = 10 * len(m_indexes)
        cost.append(cost_of_mom)
    elif len(m_indexes) == 0:
        cost.append(0)
    else:
        error.append(1)
    f_indexes = [index for index, number in enumerate(month_calendar) if number == "f"]
    if len(f_indexes) < 2:
        cost_of_father = 20 * len(f_indexes)
        cost.append(cost_of_father)
    elif len(f_indexes) == 2:
        if f_indexes[0] % 5 == 4 and f_indexes[1] % 5 == 0:
            cost.append(20 * 2)
        elif f_indexes[0] + 1 == f_indexes[1]:
            error.append(2)
        else:
            cost.append(20 * 2)
    elif len(f_indexes) > 2:
        error.append(2)
    b_indexes = [index for index, number in enumerate(month_calendar) if number == "b"]
    cost.append(30 * len(b_indexes))
    indexes_with_zip = list(zip(b_indexes[:-1], b_indexes[1:]))
    between_day = [second - first - 1 for first, second in indexes_with_zip if(second % 5) - (first % 5) > 0] + [second - first + 1 for first, second in indexes_with_zip if (second % 5) - (first % 5) < 0]
    between_day_2 = [a for a in between_day if a <= 2]
    cost_of_babysitter = sum(list(map(lambda x: x * 30, between_day_2)))
    cost.append(cost_of_babysitter)
    g_indexes = [index for index, number in enumerate(month_calendar) if number == "g"]
    remainders_g = [num % 5 for num in g_indexes]
    if not 2 in remainders_g:
        no_problem_granny = list(filter(lambda x: x % 5 != 2, g_indexes))
        cost_of_granny = 50 * len(no_problem_granny)
        cost.append(cost_of_granny)
    if 2 in remainders_g:
        count_2_for_g = remainders_g.count(2)
        if count_2_for_g <= 1:
            cost_of_granny = 50 * len(remainders_g)
            cost.append(cost_of_granny)
        elif count_2_for_g > 1:
            error.append(4)
    a1_indexes = [index for index, number in enumerate(month_calendar) if number == "a1"]
    remainders_a1 = [num % 5 for num in a1_indexes]
    if 0 in remainders_a1:
        error.append(5)
    elif 2 in remainders_a1:
        error.append(5)
    elif 3 in remainders_a1:
        error.append(5)
    else:
        no_problem_a1 = list(filter(lambda x: x % 5 == 1, a1_indexes)) + list(filter(lambda x: x % 5 == 4, a1_indexes))
        cost.append(32 * len(no_problem_a1))
    a2_indexes = [index for index, number in enumerate(month_calendar) if number == "a2"]
    remainders_a2 = [num % 5 for num in a2_indexes]
    string_list = "".join(month_calendar)
    a1a2 = string_list.find("a1a2")
    if a1a2 != -1:
        k = [a for a in a1_indexes if a+1 in a2_indexes]
        k_1 = [num % 5 for num in k]
        k_2 = [a for a in k_1 if a != 4]
        if len(k_2) > 0:
            error.append(6)
        else:
            cost.append(27 * len(a2_indexes))
    else:
        cost.append(27 * len(a2_indexes))
    n_indexes = [index for index, number in enumerate(month_calendar) if number == "n"]
    remainders_n = [num % 5 for num in n_indexes]
    if 3 in remainders_n:
        error.append(7)
    elif 4 in remainders_n:
        error.append(7)
    else:
        cost_of_neighbour_lady = sum(list(map(lambda x: pow(5, x), [day for day in range(1,len(n_indexes))])))
        cost.append(cost_of_neighbour_lady)
    if len(error) > 0:
        return(error)
    else:
        return(sum(cost))