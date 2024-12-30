USE [Banking] -- Make sure your DB is this name

-- Create the table in the specified schema
CREATE TABLE dbo.Branch (
    BranchID INT PRIMARY KEY NOT NULL,
    BranchName NVARCHAR(100) NOT NULL,
    BranchLocation NVARCHAR(100) NOT NULL
);

CREATE TABLE dbo.Transactions (
    TransactionID INT PRIMARY KEY NOT NULL,
    AccountID INT NOT NULL FOREIGN KEY REFERENCES dbo.Accounts(AccountID),
    TransactionDate DATETIME NOT NULL,
    Amount DECIMAL(15, 2) NOT NULL,
    TransactionType NVARCHAR(50) NOT NULL
);

CREATE TABLE dbo.Loans (
    LoanID INT PRIMARY KEY NOT NULL,
    CustomerID INT NOT NULL FOREIGN KEY REFERENCES dbo.Customer(CustomerID),
    LoanAmount DECIMAL(15, 2) NOT NULL,
    LoanType NVARCHAR(50) NOT NULL,
    InterestRate DECIMAL(5, 2) NOT NULL,
    LoanStatus NVARCHAR(50) NOT NULL  -- e.g., 'Pending', 'Approved', 'Rejected'
);

CREATE TABLE dbo.Customer (
    CustomerID INT PRIMARY KEY NOT NULL,
    FirstName VARCHAR(100) NOT NULL,
    LastName VARCHAR(100) NOT NULL,
    DateOfBirth INT NOT NULL,  -- Consider changing to DATE type for better accuracy
    Email VARCHAR(100) NOT NULL,
    PhoneNumber INT NOT NULL,
    Address VARCHAR(100)
);

CREATE TABLE dbo.Accounts (
    AccountID INT PRIMARY KEY NOT NULL,
    CustomerID INT NOT NULL FOREIGN KEY REFERENCES dbo.Customer(CustomerID),
    BranchID INT NOT NULL FOREIGN KEY REFERENCES dbo.Branch(BranchID),
    Name NVARCHAR(50) NOT NULL,
    Email NVARCHAR(100) NOT NULL
);

CREATE TABLE dbo.Cash (
    AccountID INT NOT NULL FOREIGN KEY REFERENCES dbo.Accounts(AccountID),
    Checking INT NOT NULL,
    Savings INT NOT NULL,
    Interest INT NOT NULL
);
GO