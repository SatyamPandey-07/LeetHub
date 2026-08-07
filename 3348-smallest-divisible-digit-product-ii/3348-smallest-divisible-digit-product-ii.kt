class Solution {
    private val kFactorCounts = arrayOf(
        emptyMap<Int, Int>(),
        emptyMap<Int, Int>(),
        mapOf(2 to 1),
        mapOf(3 to 1),
        mapOf(2 to 2),
        mapOf(5 to 1),
        mapOf(2 to 1, 3 to 1),
        mapOf(7 to 1),
        mapOf(2 to 3),
        mapOf(3 to 2)
    )

    fun smallestNumber(num: String, t: Long): String {
        val (primeCount, isDivisible) = getPrimeCount(t)
        if (!isDivisible) return "-1"

        val factorCount = getFactorCount(primeCount)
        if (sumValues(factorCount) > num.length) {
            return construct(factorCount)
        }

        var primeCountPrefix = getPrimeCountFromString(num)
        var firstZeroIndex = num.indexOf('0')
        if (firstZeroIndex == -1) {
            firstZeroIndex = num.length
            if (isSubset(primeCount, primeCountPrefix)) {
                return num
            }
        }

        val n = num.length
        val chars = num.toCharArray()

        for (i in n - 1 downTo 0) {
            val d = chars[i] - '0'
            primeCountPrefix = subtract(primeCountPrefix, kFactorCounts[d])
            val spaceAfterThisDigit = n - 1 - i
            if (i > firstZeroIndex) continue

            for (biggerDigit in d + 1..9) {
                val factorsAfterReplacement = getFactorCount(
                    subtract(subtract(primeCount, primeCountPrefix), kFactorCounts[biggerDigit])
                )
                if (sumValues(factorsAfterReplacement) <= spaceAfterThisDigit) {
                    val fillOnes = spaceAfterThisDigit - sumValues(factorsAfterReplacement)
                    val sb = StringBuilder()
                    sb.append(num.substring(0, i))
                    sb.append(biggerDigit)
                    repeat(fillOnes) { sb.append('1') }
                    sb.append(construct(factorsAfterReplacement))
                    return sb.toString()
                }
            }
        }

        val factorsAfterExtension = getFactorCount(primeCount)
        val sb = StringBuilder()
        repeat(n + 1 - sumValues(factorsAfterExtension)) { sb.append('1') }
        sb.append(construct(factorsAfterExtension))
        return sb.toString()
    }

    private fun getPrimeCount(t: Long): Pair<Map<Int, Int>, Boolean> {
        var temp = t
        val count = mutableMapOf(2 to 0, 3 to 0, 5 to 0, 7 to 0)
        for (prime in intArrayOf(2, 3, 5, 7)) {
            while (temp % prime == 0L) {
                temp /= prime
                count[prime] = count[prime]!! + 1
            }
        }
        return Pair(count, temp == 1L)
    }

    private fun getPrimeCountFromString(s: String): Map<Int, Int> {
        val count = mutableMapOf(2 to 0, 3 to 0, 5 to 0, 7 to 0)
        for (ch in s) {
            val d = ch - '0'
            if (d in kFactorCounts.indices) {
                for ((prime, freq) in kFactorCounts[d]) {
                    count[prime] = (count[prime] ?: 0) + freq
                }
            }
        }
        return count
    }

    private fun getFactorCount(primeCount: Map<Int, Int>): Map<Int, Int> {
        var c2 = primeCount[2] ?: 0
        var c3 = primeCount[3] ?: 0
        val c5 = primeCount[5] ?: 0
        val c7 = primeCount[7] ?: 0

        val count8 = c2 / 3
        var remaining2 = c2 % 3
        val count9 = c3 / 2
        var count3 = c3 % 2
        
        var count4 = remaining2 / 2
        var count2 = remaining2 % 2

        var count6 = 0
        if (count2 == 1 && count3 == 1) {
            count2 = 0
            count3 = 0
            count6 = 1
        }
        if (count3 == 1 && count4 == 1) {
            count2 = 1
            count6 = 1
            count3 = 0
            count4 = 0
        }

        val res = mutableMapOf<Int, Int>()
        if (count2 > 0) res[2] = count2
        if (count3 > 0) res[3] = count3
        if (count4 > 0) res[4] = count4
        if (c5 > 0) res[5] = c5
        if (count6 > 0) res[6] = count6
        if (c7 > 0) res[7] = c7
        if (count8 > 0) res[8] = count8
        if (count9 > 0) res[9] = count9
        return res
    }

    private fun sumValues(map: Map<Int, Int>): Int = map.values.sum()

    private fun isSubset(target: Map<Int, Int>, current: Map<Int, Int>): Boolean {
        for ((k, v) in target) {
            if ((current[k] ?: 0) < v) return false
        }
        return true
    }

    private fun subtract(current: Map<Int, Int>, toSubtract: Map<Int, Int>): Map<Int, Int> {
        val res = current.toMutableMap()
        for ((k, v) in toSubtract) {
            res[k] = Math.max(0, (res[k] ?: 0) - v)
        }
        return res
    }

    private fun construct(factorCount: Map<Int, Int>): String {
        val sb = StringBuilder()
        for (digit in 2..9) {
            val freq = factorCount[digit] ?: 0
            repeat(freq) { sb.append(digit) }
        }
        return sb.toString()
    }
}