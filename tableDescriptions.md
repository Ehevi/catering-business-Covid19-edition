# Opisy tabel
### ADDRESS
Tabela przechowująca dane o adresach osobowych i firmowych
```sql
USE [u_cyra_1]
GO

/****** Object:  Table [dbo].[address]    Script Date: 24.12.2020 15:25:47 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[address](
	[address_id] [int] IDENTITY(1,1) NOT NULL,
	[street] [nvarchar](50) NOT NULL,
	[city_id] [int] NOT NULL,
 CONSTRAINT [PK_address] PRIMARY KEY CLUSTERED 
(
	[address_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[address]  WITH CHECK ADD  CONSTRAINT [FK_address_cities] FOREIGN KEY([city_id])
REFERENCES [dbo].[cities] ([city_id])
GO

ALTER TABLE [dbo].[address] CHECK CONSTRAINT [FK_address_cities]
GO
```

### CATEGORIES
Tabela przechowująca dane o kategoriach potraw znajdujących się w menu (np. _owoce morza_)
```sql
USE [u_cyra_1]
GO

/****** Object:  Table [dbo].[categories]    Script Date: 24.12.2020 15:31:11 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[categories](
	[category_id] [int] IDENTITY(1,1) NOT NULL,
	[category_name] [nvarchar](50) NOT NULL,
 CONSTRAINT [PK_categories] PRIMARY KEY CLUSTERED 
(
	[category_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
```

### CITIES
Tabela przechowująca dane o miastach znajdujących się w bazie danych
```sql
USE [u_cyra_1]
GO

/****** Object:  Table [dbo].[cities]    Script Date: 24.12.2020 15:34:42 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[cities](
	[city_id] [int] IDENTITY(1,1) NOT NULL,
	[city_name] [nvarchar](50) NOT NULL,
	[country_id] [int] NOT NULL,
 CONSTRAINT [PK_cities] PRIMARY KEY CLUSTERED 
(
	[city_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[cities]  WITH CHECK ADD  CONSTRAINT [FK_cities_countries] FOREIGN KEY([country_id])
REFERENCES [dbo].[countries] ([country_id])
GO

ALTER TABLE [dbo].[cities] CHECK CONSTRAINT [FK_cities_countries]
GO
```

### COMPANIES
Tabela przechowująca dane o klientach firmowych.
email: unikalny i zawiera '@'
NIP: 10 cyfr(znaki numeryczne), unikalny
phone: unikalny, wyłącznie znaki numeryczne
```sql
USE [u_cyra_1]
GO

/****** Object:  Table [dbo].[companies]    Script Date: 24.12.2020 14:29:26 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[companies](
	[company_id] [int] IDENTITY(1,1) NOT NULL,
	[customer_id] [int] NOT NULL,
	[company_name] [nvarchar](50) NOT NULL,
	[address_id] [int] NOT NULL,
	[phone] [nvarchar](50) NOT NULL,
	[email] [nvarchar](50) NOT NULL,
	[NIP] [nvarchar](50) NOT NULL,
 CONSTRAINT [PK_companies] PRIMARY KEY CLUSTERED 
(
	[company_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],
 CONSTRAINT [Unique_Company_Address] UNIQUE NONCLUSTERED 
(
	[address_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],
 CONSTRAINT [Unique_Customer_ID] UNIQUE NONCLUSTERED 
(
	[customer_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[companies]  WITH CHECK ADD  CONSTRAINT [FK_companies_address] FOREIGN KEY([address_id])
REFERENCES [dbo].[address] ([address_id])
GO

ALTER TABLE [dbo].[companies] CHECK CONSTRAINT [FK_companies_address]
GO

ALTER TABLE [dbo].[companies]  WITH CHECK ADD  CONSTRAINT [FK_companies_customers] FOREIGN KEY([customer_id])
REFERENCES [dbo].[customers] ([customer_id])
GO

ALTER TABLE [dbo].[companies] CHECK CONSTRAINT [FK_companies_customers]
GO
```

### COMPANIES EMPLOYEES
Tabela zawierająca informacje o pracownikach klientów firmowych.
```sql
USE [u_cyra_1]
GO

/****** Object:  Table [dbo].[companies_employees]    Script Date: 24.12.2020 15:39:30 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[companies_employees](
	[person_id] [int] NOT NULL,
	[company_id] [int] NOT NULL,
 CONSTRAINT [PK_companies_employees] PRIMARY KEY CLUSTERED 
(
	[person_id] ASC,
	[company_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[companies_employees]  WITH CHECK ADD  CONSTRAINT [FK_companies_employees_companies] FOREIGN KEY([company_id])
REFERENCES [dbo].[companies] ([company_id])
GO

ALTER TABLE [dbo].[companies_employees] CHECK CONSTRAINT [FK_companies_employees_companies]
GO

ALTER TABLE [dbo].[companies_employees]  WITH CHECK ADD  CONSTRAINT [FK_companies_employees_person] FOREIGN KEY([person_id])
REFERENCES [dbo].[person] ([person_id])
GO

ALTER TABLE [dbo].[companies_employees] CHECK CONSTRAINT [FK_companies_employees_person]
GO
```

### COUNRIES
Słownik państw występujących w adresach osobowych i firmowych.
```sql
USE [u_cyra_1]
GO

/****** Object:  Table [dbo].[countries]    Script Date: 24.12.2020 15:40:57 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[countries](
	[country_id] [int] IDENTITY(1,1) NOT NULL,
	[country_name] [nvarchar](50) NOT NULL,
 CONSTRAINT [PK_countries] PRIMARY KEY CLUSTERED 
(
	[country_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
```

### CUSTOMERS
Tabela przechowująca ID klientów
```sql
USE [u_cyra_1]
GO

/****** Object:  Table [dbo].[customers]    Script Date: 24.12.2020 15:42:12 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[customers](
	[customer_id] [int] IDENTITY(1,1) NOT NULL,
 CONSTRAINT [PK_customers] PRIMARY KEY CLUSTERED 
(
	[customer_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
```

### CUSTOMERS_DICSOUNTS
Tabela przechowująca dane o programach rabatowych poszczególnych klientów
```sql
USE [u_cyra_1]
GO

/****** Object:  Table [dbo].[customers_discounts]    Script Date: 24.12.2020 15:43:18 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[customers_discounts](
	[customer_id] [int] NOT NULL,
	[program_id] [int] NOT NULL,
	[date_start_time] [datetime2](7) NOT NULL,
 CONSTRAINT [PK_customers_discounts] PRIMARY KEY CLUSTERED 
(
	[customer_id] ASC,
	[program_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[customers_discounts]  WITH CHECK ADD  CONSTRAINT [FK_customers_discounts_customers] FOREIGN KEY([customer_id])
REFERENCES [dbo].[customers] ([customer_id])
GO

ALTER TABLE [dbo].[customers_discounts] CHECK CONSTRAINT [FK_customers_discounts_customers]
GO

ALTER TABLE [dbo].[customers_discounts]  WITH CHECK ADD  CONSTRAINT [FK_customers_discounts_programs] FOREIGN KEY([program_id])
REFERENCES [dbo].[programs] ([program_id])
GO

ALTER TABLE [dbo].[customers_discounts] CHECK CONSTRAINT [FK_customers_discounts_programs]
GO
```

### DISCOUNT_DATA
Tabela przechowująca dane dotyczące zmiennych występujących jako wartości liczbowe w poszczególnych programach rabatowych.
```sql
USE [u_cyra_1]
GO

/****** Object:  Table [dbo].[discount_data]    Script Date: 24.12.2020 15:44:31 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[discount_data](
	[discount_data_id] [int] IDENTITY(1,1) NOT NULL,
	[type] [nvarchar](50) NOT NULL,
	[value] [float] NOT NULL,
 CONSTRAINT [PK_discount_data] PRIMARY KEY CLUSTERED 
(
	[discount_data_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
```

### DISCOUNT_DATA_IN_PROGRAMS
Tabela przechowująca informacje o tym, jakie zmienne są przyporządkowane do poszczególnych programów rabatowych.
```sql
USE [u_cyra_1]
GO

/****** Object:  Table [dbo].[discount_data_in_programs]    Script Date: 24.12.2020 15:46:42 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[discount_data_in_programs](
	[discount_data_id] [int] NOT NULL,
	[program_id] [int] NOT NULL,
 CONSTRAINT [PK_discount_data_in_programs] PRIMARY KEY CLUSTERED 
(
	[discount_data_id] ASC,
	[program_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[discount_data_in_programs]  WITH CHECK ADD  CONSTRAINT [FK_discount_data_in_programs_discount_data] FOREIGN KEY([discount_data_id])
REFERENCES [dbo].[discount_data] ([discount_data_id])
GO

ALTER TABLE [dbo].[discount_data_in_programs] CHECK CONSTRAINT [FK_discount_data_in_programs_discount_data]
GO

ALTER TABLE [dbo].[discount_data_in_programs]  WITH CHECK ADD  CONSTRAINT [FK_discount_data_in_programs_programs] FOREIGN KEY([program_id])
REFERENCES [dbo].[programs] ([program_id])
GO

ALTER TABLE [dbo].[discount_data_in_programs] CHECK CONSTRAINT [FK_discount_data_in_programs_programs]
GO
```

### EMPLOYEES
Tabela wskazująca na dane osób pracujących w usługach gastronomicznych.
```sql
USE [u_cyra_1]
GO

/****** Object:  Table [dbo].[employees]    Script Date: 24.12.2020 15:48:23 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[employees](
	[employee_id] [int] NOT NULL,
 CONSTRAINT [PK_employees] PRIMARY KEY CLUSTERED 
(
	[employee_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
```

### INDIVIDUAL
Tabela przechowująca dane o klientach indywidualnych
```sql
USE [u_cyra_1]
GO

/****** Object:  Table [dbo].[individual]    Script Date: 24.12.2020 15:52:21 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[individual](
	[person_id] [int] NOT NULL,
	[customer_id] [int] NOT NULL,
 CONSTRAINT [PK_individual] PRIMARY KEY CLUSTERED 
(
	[person_id] ASC,
	[customer_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],
 CONSTRAINT [Unique_I_Customer_ID] UNIQUE NONCLUSTERED 
(
	[customer_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],
 CONSTRAINT [Unique_I_person_ID] UNIQUE NONCLUSTERED 
(
	[person_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[individual]  WITH CHECK ADD  CONSTRAINT [FK_individual_customers] FOREIGN KEY([customer_id])
REFERENCES [dbo].[customers] ([customer_id])
GO

ALTER TABLE [dbo].[individual] CHECK CONSTRAINT [FK_individual_customers]
GO

ALTER TABLE [dbo].[individual]  WITH CHECK ADD  CONSTRAINT [FK_individual_person] FOREIGN KEY([person_id])
REFERENCES [dbo].[person] ([person_id])
GO

ALTER TABLE [dbo].[individual] CHECK CONSTRAINT [FK_individual_person]
GO
```
