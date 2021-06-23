memo = {
    "11" : "1",
    "12" : "3",
    "13" : "3",
    "21" : "1",
    "22" : "1",
    "23" : "2",
    "31" : "3",
    "32" : "3",
    "33" : "3"
    }

def foo(input):
    results = []
    
    if len(input) == 2:
        results.append(memo[input])
        return results

    if len(input) == 1:
        results.append(input)
        return results

    for i in range(len(input)-1):
        results_prefix = foo(input[:i+1])
        results_suffix = foo(input[i+1:])

        for j in results_prefix:
            for k in results_suffix:
                if memo[j+k] not in results:
                    results.append(memo[j+k])

    return results

print(foo("2221"))