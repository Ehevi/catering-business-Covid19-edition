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
