class Employee():

    def __init__(self, first, last, pay):
        self.first = first
        self.last = last
        self.pay = pay
        self.email = first + "." + last + "@company.com"

    def fullname(self):
        return "{} {}" .format(self.first, self.last)
    
    def apply_raise(self):
        self.pay = int(self.pay * 1.04)


emp = Employee("fname", "lname", "60000")
print(emp.fullname())


