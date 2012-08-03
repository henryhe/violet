#!/usr/bin/awk -f
/\{.*\}/ {
    line = $0
    sub(/INFO.*/, "", line)
    tmstr = "20" line 
    gsub(/-/, " ", tmstr)
    gsub(/:/, " ", tmstr)
    # 5 minutes more
    tmmax = mktime(tmstr) + 5 * 60
    tmmin = mktime(tmstr) - 604800
    sub(/[^{]+\{/, "")
    sub(/\}[^}]*$/, "")
    num = split($0, arr, ", ")
    for (i = 1; i <= num; i++)
    {
        if (arr[i] ~ /^d=/)
        {
            d = arr[i]
        }
        if (arr[i] ~ /^lu=/)
        {
            lu = arr[i]
        }
        if (arr[i] ~ /^m=/)
        {
            m = arr[i]
        }
        if (arr[i] ~ /^vs=/)
        {
            vs = arr[i]
        }
        if (arr[i] ~ /^e=/)
        {
            e = arr[i]
        }
    }
    sub(/lu=/, "", lu)
    nsam = split(lu, arr, "|")
    for (i = 1; i <= nsam; i++)
    {
        nf = split(arr[i], farr, ",")
        tmstr = farr[1]
        gsub(/-/, " ", tmstr)
        gsub(/:/, " ", tmstr)
        tm = mktime(tmstr)
        if (tm >= tmmin && tm <= tmmax)
        {
	    sub(/:/, " ",farr[1])
            printf("%s,000 [INFO]:[127.0.0.1]{at=lm&_y=%s&_x=%s&_pt=%s",            farr[1], farr[2], farr[3], farr[4])
            printf("&%s&%s&%s&%s",d,m,vs,e)
            nb = split(farr[5], barr, ";")
            base = 0
            bi = 0
            wi = 0
            for (k = 1; k <= nb; k++)
            {
                ns = split(barr[k], sarr, "@")
                if (ns == 2)
                {
                    singal = sarr[2]
                }
                else
                {
                    singal = "-113"
                }
                mat = match(sarr[1], ":")
                if (mat == 0)
                {
                    # base info
                    
                    split(sarr[1], iarr, ".")
                    if (base == 0)
                    {
                        printf("&mcc=%s&mnc=%s&lac=%s&ci=%s&ss=%s", iarr[1], iarr[2], iarr[3], iarr[4], singal)
                        base = 1
                    }
                    else
                    {
                        bi++
                        n8b_lac[bi] = iarr[3]
                        n8b_ci[bi] = iarr[4]
                        n8b_ss[bi] = singal
                    }
                }
                else
                {
                    # wifi info
                    wi++
                    wifi_mac[wi] = sarr[1]
                    wifi_ss[wi] = singal
                }
            }
            for (idx = 1; idx <= bi; idx++)
            {
                printf("&n8b_lac[]=%s", n8b_lac[idx])
            }
            for (idx = 1; idx <= bi; idx++)
            {
                printf("&n8b_ci[]=%s", n8b_ci[idx])
            }
            for (idx = 1; idx <= bi; idx++)
            {
                printf("&n8b_ss[]=%s", n8b_ss[idx])
            }
            for (idx = 1; idx <= wi; idx++)
            {
                printf("&wifi_mac[]=%s", wifi_mac[idx])
            }
            for (idx = 1; idx <= wi; idx++)
            {
                printf("&wifi_ss[]=%s", wifi_ss[idx])
            }
            printf("} 200(no_resp),0 in [1]\n")
        }
    } 
}


