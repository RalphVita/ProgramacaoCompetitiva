using Inflor.Infra.Persistence;
using System.Collections.Generic;

namespace TreinamentoInfra.Util
{
    public class SysParameter
    {
        public static string GetParameter(string valor, int? cdUnidade, string valor_default)
        {
            using (DataAccessController dac = new DataAccessController())
            {
                return GetParameter(valor, cdUnidade, valor_default, dac);
            }
        }

        public static string GetParameter(string valor, string valor_default)
        {
            return GetParameter(valor, int.Parse(Inflor.Infra.Common.CommonConfig.UserUnit), valor_default);
        }

        public static string GetParameter(string valor, string valor_default, bool parametro_global)
        {
            using (DataAccessController dac = new DataAccessController())
            {
                if (parametro_global)
                {
                    return GetParameter(valor, null, valor_default);
                }
                else
                {
                    return GetParameter(valor, int.Parse(Inflor.Infra.Common.CommonConfig.UserUnit), valor_default);
                }
            }
        }

        public static string GetParameter(string valor, int? cdUnidade, string valor_default, DataAccessController dac)
        {
            Dictionary<string, object> dic = new Dictionary<string, object>();
            dic.Add(nameof(valor), valor);
            dic.Add(nameof(cdUnidade), cdUnidade);
            dic.Add(nameof(valor_default), valor_default);

            string strQuery = $"SELECT F_GET_PARAMETRO([{nameof(valor)}], [{nameof(cdUnidade)}], [{nameof(valor_default)}]) from dual";

            return SysUtil.ExecuteSelect(strQuery, dac, dic).ToString();
        }
    }
}