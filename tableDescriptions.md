# Opisy tabel
### ADDRESS
Tabela przechowująca dane o adresach osobowych i firmowych
```MS SQL Server
CREATE TABLE [dbo].[address](
	[address_id] [int] NOT NULL,
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

ALTER TABLE [dbo].[address]  WITH CHECK ADD  CONSTRAINT [FK_address_cities] FOREIGN KEY([city_id])
REFERENCES [dbo].[cities] ([city_id])

ALTER TABLE [dbo].[address] CHECK CONSTRAINT [FK_address_cities]
