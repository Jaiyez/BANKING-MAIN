
-- Inserting a new customer
INSERT INTO dbo.Customer (CustomerID, FirstName, LastName, DateOfBirth, Email, PhoneNumber, Address) 
VALUES (1, 'John', 'Doe', 19850101, 'john.doe@example.com', 5551234567, '123 Elm St');

-- Inserting a new branch
INSERT INTO dbo.Branch (BranchID, BranchName, BranchLocation) 
VALUES (1, 'Main Branch', '123 Main St');

-- Inserting a new account
INSERT INTO dbo.Accounts (AccountID, CustomerID, BranchID, Name, Email) 
VALUES (1, 1, 1, 'John Doe Savings', 'john.doe@example.com');

-- Inserting cash details for an account
INSERT INTO dbo.Cash (AccountID, Checking, Savings, Interest) 
VALUES (1, 500, 1500, 1);

-- Insert a new transaction
INSERT INTO dbo.Transactions (TransactionID, AccountID, TransactionDate, Amount, TransactionType) 
VALUES (1, 1, GETDATE(), 100, 'Deposit');

-- Insert a new loan
INSERT INTO dbo.Loans (LoanID, CustomerID, LoanAmount, LoanType, InterestRate, LoanStatus) 
VALUES (1, 1, 5000, 'Personal Loan', 5.0, 'Approved');

-- Update a customer's email
UPDATE dbo.Customer 
SET Email = 'john.newemail@example.com' 
WHERE CustomerID = 1;

-- Retrive all transactions for an account
SELECT * 
FROM dbo.Transactions 
WHERE AccountID = 1;

-- Delete a loan
DELETE FROM dbo.Loans 
WHERE LoanID = 1;

-- Retrieve all accounts for a customer

-- 
