using Inflor.Infra.Common;
using Inflor.Infra.Internationalization;
using Inflor.Infra.Persistence;
using System;
using System.Collections.Generic;
using System.Data;
using System.Data.OleDb;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;
using System.Web;
using System.Web.UI.WebControls;

namespace TreinamentoInfra.Util
{
    public class SysUtil
    {
        /// <summary>
        /// Verifica se a extensao de um arquivo é uma planilha excel.
        /// </summary>
        /// <param name="extensao">Extensão do arquivo.</param>
        /// <returns>Retorna true ou false.</returns>
        public static bool IsPlanilhaExcel(string extensao)
        {
            Regex regex = new Regex(@"xls[x]?".ToUpper());

            Match match = regex.Match(extensao.ToUpper());

            return match.Success;
        }

        public static void UploadArquivo(string path, string nomeArquivo, ref FileUpload upload)
        {
            try
            {
                if (!Directory.Exists(path))
                {
                    Directory.CreateDirectory(path);
                }

                upload.SaveAs(path + nomeArquivo);
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        /// <summary>
        /// Função que retornara o caminho da pasta onde deverá ser gravado os arquivos de upload
        /// </summary> 
        /// <param name="key">Chave cadastrada no banco</param>
        /// <returns>retorna o caminho da pasta no diretorio</returns>
        /// <exception cref="Teste">Ex</exception>
        public static string GetPastaUpload(string key)
        {
            return GetPastaUpload(new DataAccessController(), key);
        }

        /// <summary>
        /// Função que retornara o caminho da pasta onde deverá ser gravado os arquivos de upload
        /// </summary> 
        /// <param name="key">Chave cadastrada no banco</param>
        /// <returns>retorna o caminho da pasta no diretorio</returns>
        /// <exception cref="Teste">Ex</exception>
        public static string GetPastaUpload(DataAccessController dac, string key)
        {
            object caminho = dac.ExecuteEscalar(string.Format(@"select NOM_PASTA from SIS_PASTA_UPLOAD 
                                                        where upper(DCR_ID_PASTA)=upper('{0}') and cd_unidade={1}", key, CommonConfig.UserUnit));

            if (caminho != null)
            {
                return CommonConfig.GetKey("PastaBaseUpload") + caminho.ToString();
            }
            else
            {
                throw new CommonException(Message.TranslateText(string.Format("#sys.alert.chave.nao.cadastrada. #sys.alert.verifique.chave.upload: {0}", key), true)); //CommonException(Message.Get("#sys.alert."));
            }
        }
        public static void SetMsgValorVazio(ref string dcrErro, string nomeColuna)
        {
            dcrErro += nomeColuna + ": " + Message.Get("#sys.erro.valor.vazio") + "; ";
        }

        public static void SetMsgValorInvalido(ref string dcrErro, string nomeColuna)
        {
            dcrErro += nomeColuna + ": " + Message.Get("#sys.erro.valor.invalido") + "; ";
        }

        /// <summary>
        /// Retorna o tipo do banco (DbType) de acordo com o tipo do objeto passado como parametro
        /// </summary>
        /// <param name="obj"></param>
        /// <returns></returns>
        public static DbType GetDbType(object obj)
        {
            if (obj == null)
            {
                return DbType.String;
            }
            else
            {
                switch (Type.GetTypeCode(obj.GetType()))
                {
                    case TypeCode.DateTime: return DbType.DateTime;
                    case TypeCode.Decimal: return DbType.Decimal;
                    case TypeCode.Double:
                    case TypeCode.Single: return DbType.Double;
                    case TypeCode.Int16:
                    case TypeCode.Int32:
                    //case TypeCode.Int64: return DbType.Int32; Alterado para retornar Int64, pois para variavei do tipo long estava dando erro.
                    case TypeCode.Int64: return DbType.Int64;
                    default: return DbType.String;
                }
            }
        }

        /// <summary>
        /// Executa sql efetuando replace dos parametros no formato [nomeParam] para nao dar replace em string e enviar parametros ao Oracle.
        /// O dicionario com os parametros deve ter a sua key com o mesmo nome que o parametro no sql. Exemplo:
        ///     key = cdUsuario => parametro no sql = [cdUsuario]
        /// Parametros repetidos nao precisam ser adicionados duas vezes ao dicionario.
        /// Parametros nao precisam ser adicionados em ordem ao dicionario.
        /// </summary>
        /// <param name="sql">sql a ser executado no banco</param>
        /// <param name="parametros">dicionario com parametros</param>
        /// <param name="dac"></param>
        /// <param name="fill">Caso true indica que retorna um DataTable</param>
        /// <returns>DataTable ou Object, dependendo do parametro fill</returns>
        private static object ExecuteQuery(string sql, Dictionary<string, object> parametros, DataAccessController _dac, bool fill = false)
        {
            if (string.IsNullOrWhiteSpace(sql)) return null;

            parametros = parametros ?? new Dictionary<string, object>();
            string prefixo = "[";
            string sufixo = "]";
            using (DataAccessController dac = _dac ?? new DataAccessController())
            {
                OleDbCommand comando = new OleDbCommand();

                // Expressao regular para encontrar qualquer texto entre [ e ]
                MatchCollection matches = Regex.Matches(sql, $@"\{prefixo}(.*?)\{sufixo}", RegexOptions.None);

                foreach (Match match in matches)
                {
                    string prop = match.Value.Replace(prefixo, string.Empty).Replace(sufixo, string.Empty);

                    if (parametros.Keys.Any(x => x == prop))
                    {
                        OleDbParameter paramDb = new OleDbParameter(match.Value, parametros[prop])
                        {
                            DbType = GetDbType(parametros[prop])
                        };
                        comando.Parameters.Add(paramDb);
                    }
                }

                foreach (Match match in matches)
                {
                    sql = sql.Replace(match.Value, "?");
                }

                comando.CommandText = sql;

                if (fill) return dac.Fill(comando);
                else return dac.ExecuteEscalar(comando);
            }
        }

        /// <summary>
        /// Executa sql efetuando replace dos parametros no formato ? para nao dar replace em string e enviar parametros ao Oracle.
        /// Os parametros devem ser passados na mesma ordem que eles aparecem na consulta SQL
        /// Parametros repetidos devem ser passados mais de uma vez.
        /// Exemplo:
        ///     sql: SELECT DCR_LOGIN FROM SEG_USUARIO WHERE CD_USUARIO = ? AND DCR_LOGIN LIKE ?
        ///     parametros: cdUsuario = 1, login = "inflor%"
        /// </summary>
        /// <param name="sql">sql a ser executado no banco</param>
        /// <param name="dac"></param>
        /// <param name="parametros">parametros em ordem que aparecem no select</param>
        private static object ExecuteQuery(string sql, DataAccessController _dac, bool fill, params object[] parametros)
        {
            if (string.IsNullOrWhiteSpace(sql)) return null;

            using (DataAccessController dac = _dac ?? new DataAccessController())
            {
                OleDbCommand comando = new OleDbCommand();
                if (parametros?.Length > 0)
                {
                    foreach (object param in parametros)
                    {
                        OleDbParameter dbp = new OleDbParameter()
                        {
                            Value = param,
                            DbType = GetDbType(param)
                        };
                        comando.Parameters.Add(dbp);
                    }
                }

                comando.CommandText = sql;
                if (fill) return dac.Fill(comando);
                else return dac.ExecuteEscalar(comando);
            }
        }



        /// <summary>
        /// Executa sql efetuando replace dos parametros no formato ? para nao dar replace em string e enviar parametros ao Oracle.
        /// Os parametros devem ser passados na mesma ordem que eles aparecem na consulta SQL
        /// Parametros repetidos devem ser passados mais de uma vez.
        /// Exemplo:
        ///     sql: SELECT DCR_LOGIN FROM SEG_USUARIO WHERE CD_USUARIO = ? AND DCR_LOGIN LIKE ?
        ///     parametros: cdUsuario = 1, login = "inflor%"
        /// </summary>
        /// <param name="sql">sql a ser executado no banco</param>
        /// <param name="dac"></param>
        /// <param name="parametros">parametros em ordem que aparecem no select</param>
        public static DataTable ExecuteFill(string sql, DataAccessController dac, params object[] parametros)
        {
            return (DataTable)ExecuteQuery(sql, dac, true, parametros);
        }

        /// <summary>
        /// Executa sql efetuando replace dos parametros no formato [nomeParam] para nao dar replace em string e enviar parametros ao Oracle.
        /// O dicionario com os parametros deve ter a sua key com o mesmo nome que o parametro no sql. Exemplo:
        ///     key = cdUsuario => parametro no sql = [cdUsuario]
        /// Parametros repetidos nao precisam ser adicionados duas vezes ao dicionario.
        /// Parametros nao precisam ser adicionados em ordem ao dicionario.
        /// No caso de comparacao por LIKE utilizar a porcentagem dentro da string. LIKE "inflor%"
        ///     sql: SELECT DCR_LOGIN FROM SEG_USUARIO WHERE CD_USUARIO = [cdUsuario] AND DCR_LOGIN LIKE [dcrLogin]
        /// </summary>
        /// <param name="sql">sql a ser executado no banco</param>
        /// <param name="dac"></param>
        /// <param name="parametros">dicionario com parametros</param>
        /// <returns></returns>
        public static object ExecuteSelect(string sql, DataAccessController dac, Dictionary<string, object> parametros)
        {
            /*
             * Exemplo:
            int cdUsuario = 1;
            string dcrLogin = "%inflor%";
            
            string sqlExemplo = $"SELECT DCR_LOGIN FROM SEG_USUARIO WHERE CD_USUARIO = [{nameof(cdUsuario)}] AND DCR_LOGIN LIKE [{nameof(dcrLogin)}] AND CD_USUARIO = [{nameof(cdUsuario)}]";

            Dictionary<string, object> dic = new Dictionary<string, object>();
            dic.Add(nameof(dcrLogin), dcrLogin);
            dic.Add(nameof(cdUsuario), cdUsuario);
            

            ExecuteSelect(sqlExemplo, dac, dic);
            */

            return ExecuteQuery(sql, parametros, dac);
        }

        /// <summary>
        /// Executa sql efetuando replace dos parametros no formato ? para nao dar replace em string e enviar parametros ao Oracle.
        /// Os parametros devem ser passados na mesma ordem que eles aparecem na consulta SQL
        /// Parametros repetidos devem ser passados mais de uma vez.
        /// Exemplo:
        ///     sql: SELECT DCR_LOGIN FROM SEG_USUARIO WHERE CD_USUARIO = ? AND DCR_LOGIN LIKE ?
        ///     parametros: cdUsuario = 1, login = "inflor%"
        /// </summary>
        /// <param name="sql">sql a ser executado no banco</param>
        /// <param name="dac"></param>
        /// <param name="parametros">parametros em ordem que aparecem no select</param>
        /// <returns></returns>
        public static object ExecuteSelect(string sql, DataAccessController dac, params object[] parametros)
        {
            /*
            int cdUsuario   = 1;
            string dcrLogin = "%inflor%";
            
            string sqlExemplo = $"SELECT DCR_LOGIN FROM SEG_USUARIO WHERE CD_USUARIO = ? AND DCR_LOGIN LIKE ? AND CD_USUARIO = ?";
            
            ExecuteSelect(sqlExemplo, dac, cdUsuario, dcrLogin, cdUsuario);
            */


            return ExecuteQuery(sql, dac, false, parametros);
        }
    }
}