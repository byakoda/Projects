def leader_of_list(L):
    if isinstance(L[0],str):
        return L[0]
    else:
        leader_of_list(L[0])



def easy_to_find(nested_list):
    dümdüz = []
    for item in nested_list:
        if isinstance(item, list):
            dümdüz.extend(easy_to_find(item))
        else:
            dümdüz.append(item)
    return dümdüz



def parent_finder(T, pname):
    if pname == T[0]:
        return None
    for item in T:
        if isinstance(item, list):
            if pname in item[1:]:
                return item[0]
            if pname in item[0]:
                return T[0]
            ancestor = parent_finder(item, pname)
            if ancestor:
                return ancestor
        elif isinstance(item, str):
            if pname == item:
                return T[0]
    return None


def siblings(T,pname):
    siblings_list = []
    parent_name = parent_finder(T,pname)
    if parent_name == None:
        return []
    for item in T:
        if isinstance(item,list):
            if parent_name in item[0]:
                for i in item[1:]:
                    if isinstance(i,list):
                        if leader_of_list(i) != pname:
                            siblings_list.append(leader_of_list(i))
                    elif isinstance(i,str):
                        if i != pname:
                            siblings_list.append(i)
            elif parent_name in easy_to_find(item):
                return siblings(item,pname)
        elif isinstance(item,str):
            if parent_name != item:
                continue
            elif parent_name == item:
                for j in T[1:]:
                    if isinstance(j,list):
                        if leader_of_list(j) != pname:
                            siblings_list.append(leader_of_list(j))
                    elif isinstance(j,str):
                        if j != pname:
                            siblings_list.append(j)
    return siblings_list


def amca_hala(T, pname):
    parent_name = parent_finder(T, pname)
    amcalar_halalar = []
    if parent_name:
        grandparent_name = parent_finder(T, parent_name)
        if grandparent_name:
            for item in T:
                if isinstance(item,list):
                    if grandparent_name in item[0]:
                        for i in item[1:]:
                            if isinstance(i,list):
                                if leader_of_list(i) != parent_name:
                                    amcalar_halalar.append(leader_of_list(i))
                            elif isinstance(i,str):
                                if i != parent_name:
                                    amcalar_halalar.append(i)
                    elif grandparent_name in easy_to_find(item):
                        return amca_hala(item, pname)
                elif isinstance(item,str):
                    if grandparent_name != item:
                        continue
                    elif grandparent_name == item:
                        for j in T[1:]:
                            if isinstance(j,list):
                                if leader_of_list(j) != parent_name:
                                    amcalar_halalar.append(leader_of_list(j))
                            elif isinstance(j,str):
                                if j != parent_name:
                                    amcalar_halalar.append(j)
    return amcalar_halalar


def brothers(T, pname):
    brother_list = []
    for i in siblings(T, pname):
        if i[0].islower():
            brother_list.append(i)
    return brother_list

def sisters(T, pname):
    sisters_list = []
    for i in siblings(T, pname):
        if not i[0].islower():
            sisters_list.append(i)
    return sisters_list

def aunts(T, pname):
    aunts_list = []
    for i in amca_hala(T, pname):
        if not i[0].islower():
            aunts_list.append(i)
    return aunts_list

def uncles(T, pname):
    uncles_list = []
    for i in amca_hala(T, pname):
        if i[0].islower():
            uncles_list.append(i)
    return uncles_list


def cousins(T, pname):
    cousins_list = []
    aunts_uncles = amca_hala(T, pname)
    for i in aunts_uncles:
        if not aunts_uncles:
            return []
        for item in T:
            if isinstance(item, list):
                if i in item[0]:
                    for t in item[1:]:
                        if isinstance(t, list):
                                cousins_list.append(leader_of_list(t))
                        elif isinstance(t, str):
                                cousins_list.append(t)
                elif i in easy_to_find(item):
                    return cousins(item, pname)
    return cousins_list