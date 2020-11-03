using System;
using System.Data;
using System.Data.OleDb;
using System.Globalization;
using Inflor.Infra.Common;
using Inflor.Infra.Internationalization;
using log4net;


namespace TreinamentoInfra.Util
{
    public class LeitorXls
    {
        /// <summary>
        /// Le uma planilha excel e retorna um DataTable com os dados lidos.
        /// </summary>
        /// <param name="nomeArquivo">Nome do arquivo excel.</param>
        /// <param name="pasta">Pasta onde esta alojado o arquivo excel.</param>
        /// <param name="importMixedTypes">Permite a especificação do IMEX. Se nao informado, considera Text (Recomendável)</param>
        /// <returns>DataTable com os dados lidos da planilha.</returns>
        /// 
        public static DataTable retornaXls(string nomeArquivo, string pasta, string importMixedTypes)
        {
            string arquivo = pasta + nomeArquivo;
            string cnn = string.Empty;
            string sheetName = string.Empty;

            if (importMixedTypes.ToUpper().Equals("TEXT") || importMixedTypes.ToUpper().Equals("1"))
            {
                //Como passar 1 ou TEXT como o valor da propriedade IMEX representa a mesma coisa, estou adotando essa tratativa.
                cnn = getOfficeProviderConnection(".XLS", arquivo, true, true);
            }
            else
            {
                cnn = getOfficeProviderConnection(".XLS", arquivo, true, false);
            }

            try
            {
                using (OleDbConnection cn = new OleDbConnection(cnn))
                {
                    cn.Open();
                    sheetName = cn.GetOleDbSchemaTable(OleDbSchemaGuid.Tables, null).Rows[0]["TABLE_NAME"].ToString();
                    string sql = "SELECT * FROM [" + sheetName + "]";
                    OleDbCommand cmd = new OleDbCommand(sql, cn);

                    OleDbDataAdapter da = new OleDbDataAdapter(cmd);
                    DataTable dt = new DataTable();
                    da.Fill(dt);
                    cn.Close();

                    return dt;
                }
            }
            catch (Exception ex)
            {
                //log.Error($@"Erro ao realizar leitura do arquivo Excel
                //            Parametros: 
                //                Arquivo: {arquivo}
                //                Connection String: {cnn}
                //                Nome da planilha: {sheetName}
                //            Stack Trace:
                //                {ex.StackTrace.ToString()}
                //            ");
                throw new Exception(ex.Message);
            }
        }

        public static DataTable retornaXls(string nomeArquivo, string pasta)
        {
            return retornaXls(nomeArquivo, pasta, "Text");
        }


        public static DataTable LePlanilhaExcel(string pasta, string nomeArquivo, string extensao, bool TemCabecalho = true, int indexAba = -1)
        {
            return LePlanilhaExcel(pasta, nomeArquivo, extensao, null, TemCabecalho, indexAba);
        }

        /// <summary>
        /// Lê uma planilha excel e retorna os dados lidos em um DataTable.
        /// </summary>
        /// <param name="pasta">Pasta de onde esta situada o arquivo.</param>
        /// <param name="nomeArquivo">Nome do arquivo.</param>
        /// <param name="extensao">Extensão do arquivo(XLS ou XLSX).</param>
        /// <param name="nomeTabela">Nome da Tabela - Nome da tabela tem que ser passado com $ ao final do nome, Exemplo: TESTE$</param>
        /// <param name="TemCabecalho"></param>
        /// <param name="indexAba">index da aba a ser considerada na leitura</param>
        /// <returns>DataTable com os dados lidos da planilha.</returns>
        public static DataTable LePlanilhaExcel(string pasta,
                                                string nomeArquivo,
                                                string extensao,
                                                string nomeTabela,
                                                bool TemCabecalho = true,
                                                int indexAba = -1)
        {
            string arquivo = pasta + nomeArquivo;
            string cnn = string.Empty;
            DataTable dt = new DataTable();
            string sheetName = string.Empty;
            int qtdAbas = indexAba;

            try
            {
                cnn = getOfficeProviderConnection(extensao.ToUpper(), arquivo, true, TemCabecalho ? true : false);


                if (!string.IsNullOrEmpty(cnn))
                {
                    using (OleDbConnection cn = new OleDbConnection(cnn))
                    {
                        cn.Open();

                        qtdAbas = cn.GetOleDbSchemaTable(OleDbSchemaGuid.Tables, null).Rows.Count;

                        int indexAbaLeitura = indexAba >= 0 ? indexAba : qtdAbas - 1;

                        if (string.IsNullOrEmpty(nomeTabela))
                            sheetName = cn.GetOleDbSchemaTable(OleDbSchemaGuid.Tables, null).Rows[indexAbaLeitura]["TABLE_NAME"].ToString();
                        else
                            sheetName = nomeTabela;


                        if (qtdAbas > 0)
                        {
                            //tratamento para quando a planilha tiver algum filtro, isso faz com que o execel altere o nome da aba adicionando "_" no final e gerando erro na leitura.
                            if (sheetName.EndsWith("_"))
                                sheetName = sheetName.TrimEnd('_');
                            string sql = "SELECT * FROM [" + sheetName + "]";
                            OleDbCommand cmd = new OleDbCommand(sql, cn);

                            OleDbDataAdapter da = new OleDbDataAdapter(cmd);
                            da.Fill(dt);

                        }

                        cn.Close();
                    }
                }

                return dt;
            }
            catch (Exception ex)
            {
                //log.Error($@"Erro ao realizar leitura do arquivo Excel
                //            Parametros: 
                //                Arquivo: {arquivo}
                //                Connection String: {cnn}
                //                Nome da planilha: {sheetName}
                //                Quantidades de abas da Planilha: {qtdAbas}
                //            Stack Trace:
                //                {ex.StackTrace.ToString()}
                //            ");
                throw new CommonException(ex.Message);
            }
        }

        /// <summary>
        /// Retorna um array de strings com o nome de cada coluna da planilha excel.
        /// </summary>
        /// <param name="dt"></param>
        /// <returns></returns>
        public static string[] GetNomeColunasPlanilha(DataTable dt)
        {
            string[] nomeColunas = new string[dt.Columns.Count];

            if (dt.Columns.Count > 0)
            {
                for (int i = 0; i < dt.Columns.Count; i++)
                {
                    nomeColunas[i] = dt.Columns[i].ColumnName.Replace('#', ' ');
                }
            }

            return nomeColunas;
        }

        public static string FormataVlr(string valor)
        {
            CultureInfo cultura = new CultureInfo(CommonConfig.UserLanguage);

            if (cultura.NumberFormat.CurrencyDecimalSeparator.Equals("."))
            {
                valor = valor.Replace(',', '.');
            }
            else
            {
                valor = valor.Replace('.', ',');
            }

            return valor;
        }

        /// <summary>
        /// Retorna a string do valor numerico com separador decimal padrao.
        /// </summary>
        /// <param name="strValor"></param>
        /// <returns>string com valor formatado</returns>
        public static string FormataVlrPadrao(string strValor)
        {
            Double vlrNum;
            CultureInfo cultura = new CultureInfo(CommonConfig.UserLanguage);

            if (cultura.NumberFormat.CurrencyDecimalSeparator.Equals("."))
            {
                strValor = strValor.Replace(",", "");
                strValor = strValor.Replace(".", ",");
            }
            else
            {
                strValor = strValor.Replace(".", "");
            }

            if (!Double.TryParse(strValor, NumberStyles.Float, CultureInfo.CreateSpecificCulture("pt-BR"), out vlrNum))
                throw new CommonException(Message.Get("#sys.formato.numerico.incorreto"));

            return strValor;
        }

        /// <summary>
        /// Cria uma string de conexão para o processo de leitura de arquivos do Excel, inserindo as propriedades necessárias.
        /// </summary>
        /// <param name="fileExtension">Extensão do arquivo Excel que será importado, XLS ou XLSX</param>
        /// <param name="file">Caminho do arquivo que será importado</param>
        /// <param name="HDR">Indica se deverá considerar HDR, caso seja falso a string de conexão retornada não terá essa propriedade</param>
        /// <param name="IMEX">Indica de deverá considerar IMEX, caso seja falso a string de conexão retornada não terá essa propriedade</param>
        /// <returns>String de conexão para ser utilizada em leitura de arquivos Excel</returns>
        public static string getOfficeProviderConnection(string fileExtension, string file, bool HDR, bool IMEX)
        {
            string conn, providerExcel, propExcel, HDRProp, IMEXProp;
            conn = providerExcel = propExcel = HDRProp = IMEXProp = string.Empty;


            if (HDR)
            {
                HDRProp = "HDR = Yes;";
            }

            if (IMEX)
            {
                IMEXProp = "IMEX = 1;";
            }

            switch (fileExtension.ToUpper())
            {
                case ".XLS":
                    providerExcel = SysParameter.GetParameter("PROVIDER.EXCEL", @"Provider=Microsoft.ACE.OLEDB.12.0");
                    propExcel = SysParameter.GetParameter("PROVIDER.EXCEL.XLS.EXT.PROP", @"Excel 8.0");

                    conn = ($@"{providerExcel}; Data Source={file};Extended Properties='{propExcel};{HDRProp}{IMEXProp}'");
                    break;

                case ".XLSX":
                    providerExcel = SysParameter.GetParameter("PROVIDER.EXCEL", @"Provider=Microsoft.ACE.OLEDB.14.0");
                    propExcel = SysParameter.GetParameter("PROVIDER.EXCEL.XLSX.EXT.PROP", @"Excel 14.0");

                    conn = ($@"{providerExcel}; Data Source={file};Extended Properties='{propExcel};{HDRProp}{IMEXProp}'");
                    break;

                default:
                    throw new Exception("sys.label.formato.invalido");
            }

            return conn;
        }
    }
}