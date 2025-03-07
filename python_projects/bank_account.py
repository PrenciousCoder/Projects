
import random

class BankAccount():
    Bank_acc_number=1000
    
    def __init__(self, name,balance=0):
        self.name=name
        self.balance=balance
        self.acc_number=BankAccount.Bank_acc_number
        BankAccount.Bank_acc_number=BankAccount.Bank_acc_number+1
    
    def deposit(self,amount):
        if amount>0:
            self.balance=self.balance+amount
            return self.balance
        else:
            return "Enter a Valid Amount"
    
    def withdrawal(self,amount):
        if amount<=self.balance:
            print(f"You withdrawed: {amount}")
            print(f"Remaining Balance: {self.balance}")
            self.balance=self.balance-amount
    
    def get_balance(self):
        return self.balance
    
    def display_account_details(self):
        print(f"Name of Account Holder: {self.name}")
        print(f"Account Number: {self.acc_number}")
        print(f"Available Balance: {self.balance}")

def main():
    bit=True
    print("             ###WELCOME TO XYZ BANK:###               ")
    #action=input("What would you like to do: ")
    while bit==True:
        action=input("What would you like to do: ")
        if action=="open account":
            name=input("Enter your Name :")
            balance=int(input("Enter the opening balance: "))
            acc1=BankAccount(name,balance)
            acc1.display_account_details()
        elif action=="deposit":
            amount=int(input("How much would you like to deposite?: "))
            acc1.deposit(amount)
        elif  action=="withdraw":
            amount=float(input("How much would you like to withdraw? "))
            acc1.withdrawal(amount)
            print(f"Here is your: ${amount}")
            print(f"Remaining Balance: {acc1.get_balance()}")
        elif  action=="check balance":
            print(f"Current balance: {acc1.get_balance()}")
        elif action=="Account info":
            acc1.display_account_details()
        elif action=="exit":
            bit=False
        else:
            print("Invalid Action")


main()
        
    
        
            
        
