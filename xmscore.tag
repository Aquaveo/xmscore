<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>math.cpp</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/math/</path>
    <filename>math_8cpp</filename>
    <includes id="math_8h" name="math.h" local="no" imported="no">xmscore/math/math.h</includes>
    <includes id="math_8t_8h" name="math.t.h" local="no" imported="no">xmscore/math/math.t.h</includes>
    <includes id="pt_8h" name="pt.h" local="no" imported="no">xmscore/points/pt.h</includes>
    <includes id="_test_tools_8h" name="TestTools.h" local="no" imported="no">xmscore/testing/TestTools.h</includes>
  </compound>
  <compound kind="file">
    <name>math.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/math/</path>
    <filename>math_8h</filename>
    <namespace>xms</namespace>
    <member kind="function">
      <type>int</type>
      <name>Round</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>adfc1700dbd9064558f9fc863ebf041eb</anchor>
      <arglist>(_T a)</arglist>
    </member>
    <member kind="function">
      <type>_T</type>
      <name>Miabs</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a84070d6a77796325193e66c78ca154aa</anchor>
      <arglist>(_T a)</arglist>
    </member>
    <member kind="function">
      <type>_T</type>
      <name>Mfabs</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a05c138381112b821d1b787e9a00ec7bf</anchor>
      <arglist>(_T a)</arglist>
    </member>
    <member kind="function">
      <type>_T</type>
      <name>Mmax</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a1ebfb4727e5e32fd9c5ff54bbe1eb00d</anchor>
      <arglist>(_T a, _U b)</arglist>
    </member>
    <member kind="function">
      <type>_T</type>
      <name>Mmin</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a49767d69c41924570a9ba7618a1ab347</anchor>
      <arglist>(_T a, _U b)</arglist>
    </member>
    <member kind="function">
      <type>_T</type>
      <name>Mmax3</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a704792bfcc46cdf8985064c2aa682cbf</anchor>
      <arglist>(_T a, _U b, _V c)</arglist>
    </member>
    <member kind="function">
      <type>_T</type>
      <name>Mmin3</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aff5b55ba164ee1413aa3642672016f88</anchor>
      <arglist>(_T a, _U b, _V c)</arglist>
    </member>
    <member kind="function">
      <type>_T</type>
      <name>sqr</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aa101a2a7d9f16080d4ff39ef821e36cf</anchor>
      <arglist>(const _T x)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Mdist</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a98aa9ce14bd15da1a7bf8967c9fe7859</anchor>
      <arglist>(_T x1, _U y1, _V x2, _W y2)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>MdistSq</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af8a2d48751fbb04d767cc893412654b1</anchor>
      <arglist>(_T x1, _U y1, _V x2, _W y2)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Mdist</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aadbee364d0afc6d54374e612e2c48ab4</anchor>
      <arglist>(X1 x1, Y1 y1, Z1 z1, X2 x2, Y2 y2, Z2 z2)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>MagSquared</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5fbdecf465138bd8c97d71bb82fa7681</anchor>
      <arglist>(_T const x, _T const y, _T const z=0, _T const w=0)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Mag</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>adfc065e9706d90143ae53420a9cf1b2c</anchor>
      <arglist>(_T const x, _T const y, _T const z=0, _T const w=0)</arglist>
    </member>
    <member kind="function">
      <type>_T</type>
      <name>Clamp</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a2fd4ced1304195c63c72c132a2318891</anchor>
      <arglist>(_T a_in, _T a_min, _T a_max)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EQ_EPS</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aae3e3dee54b4e049573f92c74a38f79f</anchor>
      <arglist>(_T A, _U B, _V epsilon)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>LT_EPS</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aaff8b48b5ad5f026e35bc38f1aab1ca7</anchor>
      <arglist>(_T A, _U B, _V epsilon)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GT_EPS</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a661b4e1380df8833eb664d864a0868e0</anchor>
      <arglist>(_T A, _U B, _V epsilon)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>LTEQ_EPS</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a68b550210e6ca81a802f5ba2fc88c2e7</anchor>
      <arglist>(_T A, _U B, _V epsilon)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GTEQ_EPS</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4c0dd874e2af06c9ea53bee53a0f8809</anchor>
      <arglist>(_T A, _U B, _V epsilon)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EQ_TOL</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad2b764be90f289082998491db1b52711</anchor>
      <arglist>(const _T &amp;A, const _U &amp;B, const _V &amp;tolerance)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>LT_TOL</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4cfdbe3e6a4d961c82a96926619f5a9f</anchor>
      <arglist>(_T A, _U B, _V tolerance)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GT_TOL</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab8190cb81d709d785efaa01409c342c2</anchor>
      <arglist>(_T A, _U B, _V tolerance)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>LTEQ_TOL</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6e651752f23c660cebe5561ae9e9b374</anchor>
      <arglist>(_T A, _U B, _V tol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GTEQ_TOL</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae0787a6aa8fbfb21f298cea14409af25</anchor>
      <arglist>(_T A, _U B, _V tol)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>math.t.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/math/</path>
    <filename>math_8t_8h</filename>
    <class kind="class">MathUnitTests</class>
  </compound>
  <compound kind="file">
    <name>base_macros.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/misc/</path>
    <filename>base__macros_8h</filename>
    <namespace>xms</namespace>
    <member kind="define">
      <type>#define</type>
      <name>XM_DISALLOW_COPY_AND_ASSIGN</name>
      <anchorfile>base__macros_8h.html</anchorfile>
      <anchor>a5580a05bffe13e3b72158e01e41c3945</anchor>
      <arglist>(TypeName)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>boost_defines.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/misc/</path>
    <filename>boost__defines_8h</filename>
    <namespace>xms</namespace>
    <member kind="define">
      <type>#define</type>
      <name>BSHP</name>
      <anchorfile>boost__defines_8h.html</anchorfile>
      <anchor>a37efc6913312f9271e2ea37f1acbc2dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BSCP</name>
      <anchorfile>boost__defines_8h.html</anchorfile>
      <anchor>aab05c18215f36168f2af35f0177d7f46</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BDPC</name>
      <anchorfile>boost__defines_8h.html</anchorfile>
      <anchor>a076573488d41fb023a832c41a9310aa2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BSPC</name>
      <anchorfile>boost__defines_8h.html</anchorfile>
      <anchor>a83900d59da231b6dba6f5e307715c531</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BWP</name>
      <anchorfile>boost__defines_8h.html</anchorfile>
      <anchor>aec9b913813088bbcdc8fdbe46ef1aaa6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FOREACH</name>
      <anchorfile>boost__defines_8h.html</anchorfile>
      <anchor>a7454d4a34d1c455e775211e6c1198fdb</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; T &gt;</type>
      <name>CopyBSHP</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3d6d80550e13f3bd87b7d6680070ba39</anchor>
      <arglist>(const BSHP&lt; T &gt; &amp;a_in)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>carray.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/misc/</path>
    <filename>carray_8h</filename>
    <namespace>xms</namespace>
    <member kind="define">
      <type>#define</type>
      <name>XM_COUNTOF</name>
      <anchorfile>carray_8h.html</anchorfile>
      <anchor>af1097652ed11821b95b2e84b41377016</anchor>
      <arglist>(array)</arglist>
    </member>
    <member kind="function">
      <type>char(&amp;</type>
      <name>caArraySizeHelper</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a7872de9419f714a93ed1c4ce76d35a6c</anchor>
      <arglist>(T(&amp;array)[N]))[N]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>color_defines.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/misc/</path>
    <filename>color__defines_8h</filename>
    <includes id="environment_8h" name="environment.h" local="no" imported="no">xmscore/misc/environment.h</includes>
    <namespace>xms</namespace>
    <member kind="define">
      <type>#define</type>
      <name>XM_LOBYTE</name>
      <anchorfile>color__defines_8h.html</anchorfile>
      <anchor>a403390d4572778be289c1e04ed263bd9</anchor>
      <arglist>(w)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XmsGetRValue</name>
      <anchorfile>color__defines_8h.html</anchorfile>
      <anchor>abda0e205f09cddfd649595139e1b6fac</anchor>
      <arglist>(rgb)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XmsGetGValue</name>
      <anchorfile>color__defines_8h.html</anchorfile>
      <anchor>aa20345c7626087d691b28e96550b6254</anchor>
      <arglist>(rgb)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XmsGetBValue</name>
      <anchorfile>color__defines_8h.html</anchorfile>
      <anchor>a3a894afbdb46e64399e20270de2c7b3c</anchor>
      <arglist>(rgb)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XmsRGB</name>
      <anchorfile>color__defines_8h.html</anchorfile>
      <anchor>aabfc7e8a25fc34d5218cbb07d5c48eda</anchor>
      <arglist>(r, g, b)</arglist>
    </member>
    <member kind="typedef">
      <type>unsigned long</type>
      <name>XM_DWORD</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9914eef47ba2ef59310b7792b11f9bc0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>XM_ULONG_PTR</type>
      <name>XM_DWORD_PTR</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aef89aab782c051695b1f554a93808789</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned short</type>
      <name>XM_WORD</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4d480ea25f374957ddccd969cc9df34a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned char</type>
      <name>XM_BYTE</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af746940725ac9170fe7618a41cd2e225</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>XM_DWORD</type>
      <name>XM_COLORREF</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aeacfbf0add472c121123b8206a36daf8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>DynBitset.cpp</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/misc/</path>
    <filename>_dyn_bitset_8cpp</filename>
    <includes id="_dyn_bitset_8h" name="DynBitset.h" local="no" imported="no">xmscore/misc/DynBitset.h</includes>
    <namespace>xms</namespace>
    <member kind="function">
      <type>void</type>
      <name>VecBooleanToDynBitset</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a07a9a5ed39e6326c5725622af98f4856</anchor>
      <arglist>(const std::vector&lt; unsigned char &gt; &amp;a_from, DynBitset &amp;a_to)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DynBitsetToVecBoolean</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>afde2102c1e6c433c09ef13194a92feeb</anchor>
      <arglist>(const DynBitset &amp;a_from, std::vector&lt; unsigned char &gt; &amp;a_to)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>DynBitset.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/misc/</path>
    <filename>_dyn_bitset_8h</filename>
    <namespace>xms</namespace>
    <member kind="typedef">
      <type>boost::dynamic_bitset&lt; size_t &gt;</type>
      <name>DynBitset</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aba8c1eacfbbd2d1f45cef2fd55a35d93</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>environment.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/misc/</path>
    <filename>environment_8h</filename>
  </compound>
  <compound kind="file">
    <name>Observer.cpp</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/misc/</path>
    <filename>_observer_8cpp</filename>
    <includes id="_observer_8h" name="Observer.h" local="no" imported="no">xmscore/misc/Observer.h</includes>
    <includes id="_observer_8t_8h" name="Observer.t.h" local="no" imported="no">xmscore/misc/Observer.t.h</includes>
    <includes id="math_8h" name="math.h" local="no" imported="no">xmscore/math/math.h</includes>
    <includes id="_test_tools_8h" name="TestTools.h" local="no" imported="no">xmscore/testing/TestTools.h</includes>
    <class kind="class">xms::Observer::impl</class>
    <class kind="class">MockObserver</class>
    <class kind="class">MockMesher</class>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>Observer.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/misc/</path>
    <filename>_observer_8h</filename>
    <includes id="boost__defines_8h" name="boost_defines.h" local="no" imported="no">xmscore/misc/boost_defines.h</includes>
    <class kind="class">xms::Observer</class>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>Observer.t.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/misc/</path>
    <filename>_observer_8t_8h</filename>
    <class kind="class">ObserverIntermediateTests</class>
  </compound>
  <compound kind="file">
    <name>Progress.cpp</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/misc/</path>
    <filename>_progress_8cpp</filename>
    <includes id="_progress_8h" name="Progress.h" local="no" imported="no">xmscore/misc/Progress.h</includes>
    <includes id="_xm_error_8h" name="XmError.h" local="no" imported="no">xmscore/misc/XmError.h</includes>
    <includes id="_progress_8t_8h" name="Progress.t.h" local="no" imported="no">xmscore/misc/Progress.t.h</includes>
    <class kind="class">MockProgressListener</class>
    <namespace>xms</namespace>
    <member kind="function">
      <type>BSHP&lt; ProgressListener &gt; &amp;</type>
      <name>iListener</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4e7e0625acb9a639f0a22b16a7c40267</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Progress.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/misc/</path>
    <filename>_progress_8h</filename>
    <includes id="boost__defines_8h" name="boost_defines.h" local="no" imported="no">xmscore/misc/boost_defines.h</includes>
    <class kind="class">xms::Progress</class>
    <class kind="class">xms::ProgressListener</class>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>Progress.t.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/misc/</path>
    <filename>_progress_8t_8h</filename>
    <class kind="class">ProgressUnitTests</class>
  </compound>
  <compound kind="file">
    <name>Singleton.cpp</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/misc/</path>
    <filename>_singleton_8cpp</filename>
    <includes id="_singleton_8h" name="Singleton.h" local="no" imported="no">xmscore/misc/Singleton.h</includes>
  </compound>
  <compound kind="file">
    <name>Singleton.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/misc/</path>
    <filename>_singleton_8h</filename>
    <class kind="class">xms::Singleton</class>
    <class kind="class">xms::SharedSingleton</class>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>StringUtil.cpp</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/misc/</path>
    <filename>_string_util_8cpp</filename>
    <includes id="_string_util_8h" name="StringUtil.h" local="no" imported="no">xmscore/misc/StringUtil.h</includes>
    <includes id="math_8h" name="math.h" local="no" imported="no">xmscore/math/math.h</includes>
    <includes id="_xm_error_8h" name="XmError.h" local="no" imported="no">xmscore/misc/XmError.h</includes>
    <includes id="_string_util_8t_8h" name="StringUtil.t.h" local="no" imported="no">xmscore/misc/StringUtil.t.h</includes>
    <includes id="_test_tools_8h" name="TestTools.h" local="no" imported="no">xmscore/testing/TestTools.h</includes>
    <namespace>xms</namespace>
    <member kind="function">
      <type>unsigned int</type>
      <name>stCountChar</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a66dc21c168b37fd14baa201e35d24303</anchor>
      <arglist>(const std::string &amp;str, char c)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>stNumeric</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab0b7eb9e82512404cfbc9a27b6559581</anchor>
      <arglist>(const std::string &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>stScientificNotation</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ace822764b0cde4e3baf45bda5a79278e</anchor>
      <arglist>(const std::string &amp;str, bool check_numeric)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stChangeExtendedAscii</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0c7be175c9d3dfece6b1ef294c2bb7a5</anchor>
      <arglist>(std::string &amp;str, bool to_extended)</arglist>
    </member>
    <member kind="function">
      <type>VecStr</type>
      <name>stExplode</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a57dc839bc15e3dd666e5dc4f760c306a</anchor>
      <arglist>(const std::string &amp;source, const std::string &amp;a_delimiter)</arglist>
    </member>
    <member kind="function">
      <type>VecStr</type>
      <name>stSplit</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a017a40f9bede43b498c72da02bd467df</anchor>
      <arglist>(const std::string &amp;a_source, const std::string &amp;a_delimiterList, bool a_delimiterCompressOn)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>stImplode</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6a337b11d65b3a9417cba2112e74b508</anchor>
      <arglist>(const std::vector&lt; std::string &gt; &amp;source, const std::string &amp;delim)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>stIndexOfElem</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aaa0728c7493daa64d15c1cb841a6a497</anchor>
      <arglist>(const VecStr &amp;a_container, const std::string &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>stTrimCopy</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a84d62f26c1fc187d83b46b84b3cf43b9</anchor>
      <arglist>(const std::string &amp;str, const std::string &amp;delim)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>stTrimLeft</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aeb97c544ba43a601c6eda91cf7b35660</anchor>
      <arglist>(std::string &amp;str, const std::string &amp;delim)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>stTrimRight</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a24b3a75ddb15e1a3af63ace78743698e</anchor>
      <arglist>(std::string &amp;str, const std::string &amp;delim)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>stTrim</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a39d7f16b6e977ae32527ea53fe4b9787</anchor>
      <arglist>(std::string &amp;str, const std::string &amp;delim)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>stReplaceCopy</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3231cbcdc9c74f4062773a434ce911d9</anchor>
      <arglist>(const std::string &amp;str, char source, char dest)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>stReplaceCopy</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae019a64c9217040cee8621d4d3d3165d</anchor>
      <arglist>(const std::string &amp;str, const std::string &amp;source, const std::string &amp;dest)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>stReplace</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac9581f4c28c356b74396dba117269ae1</anchor>
      <arglist>(std::string &amp;str, char source, char dest)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>stReplace</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a388e8a7ed3aa5ad71577af5d80e56d92</anchor>
      <arglist>(std::string &amp;str, const std::string &amp;source, const std::string &amp;dest)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>stRemoveCopy</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>abf72758241ec1e075a523e39c3b3c344</anchor>
      <arglist>(const std::string &amp;str, char source)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>stRemove</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aafff78bb96f6fbeea2f19f109a5437e2</anchor>
      <arglist>(std::string &amp;str, char source)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>stToLowerCopy</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aa23e586099822b2abf95667edda1e5ac</anchor>
      <arglist>(const std::string &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>stToLower</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a7505715e7657aaf00882cbef93bb5207</anchor>
      <arglist>(std::string &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>stToUpperCopy</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a256855911dbcfa820f371cd2e1e51dda</anchor>
      <arglist>(const std::string &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>stToUpper</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a1a830ff5f0993e00e18f160b7688587e</anchor>
      <arglist>(std::string &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>stLeftCopy</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>abaebc05a9850a63de0a2e97cd846f003</anchor>
      <arglist>(const std::string &amp;a_source, size_t const a_length)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>stLeft</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8c8313510105ac074df3d8b2bb31a19d</anchor>
      <arglist>(std::string &amp;a_source, size_t const a_length)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>stRightCopy</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aef112f15bf17156747a46651c3091327</anchor>
      <arglist>(const std::string &amp;a_source, size_t const a_length)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>stSimplified</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a923ca5adb7e740d260c6107a30eb92e4</anchor>
      <arglist>(const std::string &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>stContains</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>afd009be52d6dc920921393aefb392a47</anchor>
      <arglist>(const std::string &amp;a_container, const std::string &amp;a_substr)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>stVectorContainsString</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5dbf6882ae8b9a61712f6804976332bd</anchor>
      <arglist>(const VecStr &amp;a_container, const std::string &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>stRight</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab67b6dca5ea3213603fddba4f20dc01d</anchor>
      <arglist>(std::string &amp;a_source, size_t const a_length)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>stEqualNoCase</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a99069b19783ed6a9afce2bcf67b90509</anchor>
      <arglist>(const std::string &amp;a, const std::string &amp;b)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>stFindNoCase</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a92aeadb401decb6f069031aa823ea71c</anchor>
      <arglist>(const std::string &amp;a, const std::string &amp;b)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>stMakeUnique</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8c105a0f5188c2ffd832849a06828d56</anchor>
      <arglist>(const std::set&lt; std::string &gt; &amp;set_str, std::string &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>stStringToInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aba35915722db9ac0e5a10fbfcdcf4d3a</anchor>
      <arglist>(const std::string &amp;s, int &amp;i, int base)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>stStringToDouble</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a13129a1a44d72d661112e936365ef4cf</anchor>
      <arglist>(const std::string &amp;s, double &amp;d)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>stPrecision</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab717e5d6ed20083c488f249bd4d98659</anchor>
      <arglist>(double value, int &amp;flags, int length)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>STRstd</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac1a247a3a486723b3ce08d4e732845f3</anchor>
      <arglist>(double a_value, int a_n, int width, int flags)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>STRstd</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a1d8fdd4c8a76a30d5cdbf056aa8e96a0</anchor>
      <arglist>(float value, int n, int width, int flags)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>STRstd</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a029b7e2c274fc5487dfc32a84ea915ea</anchor>
      <arglist>(std::string value)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>StringUtil.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/misc/</path>
    <filename>_string_util_8h</filename>
    <includes id="vector_8h" name="vector.h" local="no" imported="no">xmscore/stl/vector.h</includes>
    <class kind="class">xms::StTemp2DigitExponents</class>
    <class kind="class">xms::StCommaNumpunct</class>
    <namespace>xms</namespace>
    <member kind="enumeration">
      <type></type>
      <name>PrecFlags</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a150c15c1d0a88f50f4d712f9d9be3008</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>STR_FLOAT</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a150c15c1d0a88f50f4d712f9d9be3008a48bb11800c4a7fa2d7322427b881a6c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>STR_SCIENTIFIC</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a150c15c1d0a88f50f4d712f9d9be3008a082a9602c7c50dad0fe698b5d58c8808</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>STR_USEMAXPREC</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a150c15c1d0a88f50f4d712f9d9be3008aaed962324766743f9927850945772b06</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>STR_FULLWIDTH</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a150c15c1d0a88f50f4d712f9d9be3008a0cab439cf05ec71900dadea89ec9577e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>STR_WITHCOMMAS</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a150c15c1d0a88f50f4d712f9d9be3008a6b948c99ca149c735b9f974c8269c0bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>STRstd</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a309788d8d6f39ac0cb2f7691b11e8623</anchor>
      <arglist>(T a_value, int a_n=0, int width=0, int flags=0)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>ST_WHITESPACE</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>adacac03ecb8d5f770a21dfe70ec3dc9f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>StringUtil.t.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/misc/</path>
    <filename>_string_util_8t_8h</filename>
    <class kind="class">StringUtilUnitTests</class>
  </compound>
  <compound kind="file">
    <name>XmConst.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/misc/</path>
    <filename>_xm_const_8h</filename>
    <namespace>xms</namespace>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>XM_INT_HIGHEST</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a01350319705aa8fd575e571f7dc78b39</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>XM_INT_LOWEST</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a513f1bc13007d6834be52c6867b0ddc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const unsigned int</type>
      <name>XM_UINT_HIGHEST</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3819f0281d41e53e2dd323438083bc28</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const unsigned int</type>
      <name>XM_UINT_LOWEST</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8cca2290d55e78682257cb695f78bbbe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const double</type>
      <name>XM_DBL_HIGHEST</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a2405d59c64287fc04dd46a911a4f16c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const double</type>
      <name>XM_DBL_LOWEST</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a96ffa8332bb58934b5dd1927c1f5d900</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const double</type>
      <name>XM_DBL_NEAREST_ZERO</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8526fadd03c75b447ea997bfc835c213</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const float</type>
      <name>XM_FLT_HIGHEST</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>afc9f74847c61fef850b01c89862de16b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const float</type>
      <name>XM_FLT_LOWEST</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a271eb6a5b02e4cb04e7595d9d932fa4b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const float</type>
      <name>XM_FLT_NEAREST_ZERO</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a898ed1927f8720f5ff8fdc614d2206bc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>XmError.cpp</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/misc/</path>
    <filename>_xm_error_8cpp</filename>
    <includes id="_xm_error_8h" name="XmError.h" local="no" imported="no">xmscore/misc/XmError.h</includes>
    <includes id="boost__defines_8h" name="boost_defines.h" local="no" imported="no">xmscore/misc/boost_defines.h</includes>
    <includes id="_xm_error_8t_8h" name="XmError.t.h" local="no" imported="no">xmscore/misc/XmError.t.h</includes>
    <namespace>xms</namespace>
    <member kind="function">
      <type>bool &amp;</type>
      <name>xmAsserting</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a321716f8c5b486484ad8b9b88e4cb919</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>XM0</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>acdef92522c0ad17d614cd15b6aa3bb38</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>XM1</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4c3305728b07d971cd598e0da2b6c91f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>XmError.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/misc/</path>
    <filename>_xm_error_8h</filename>
    <includes id="_xm_log_8h" name="XmLog.h" local="no" imported="no">xmscore/misc/XmLog.h</includes>
    <namespace>xms</namespace>
    <member kind="define">
      <type>#define</type>
      <name>XM_LIKELY</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>aa974d54357e1e5ce1039ace624c9a2d5</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_UNLIKELY</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>a59af96c2c6fcfdc0d6d677e04ac41945</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_FAILED</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>a23ec2302026fd78a277a01cce7b35b37</anchor>
      <arglist>(_xmresult)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_SUCCEEDED</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>a7163cabbdba6ed410b120664e521e5b2</anchor>
      <arglist>(_xmresult)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ASSERT</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>a5c82c2e747cf320d95402dfdf2fdba85</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_SUCCESS_5</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>abd0ec6bf9fce637b5340219f267671ad</anchor>
      <arglist>(x, ret, lvl, msg, ast)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_SUCCESS_3</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>af96354118e28663ed645aaf291542999</anchor>
      <arglist>(x, ret, ast)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_SUCCESS</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>acb2560d5d3eaeac4f7d7d0f8ce02f66d</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_SUCCESS_NO_ASSERT</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>af7a141ecf5a5e956bedccfffdecdf0b2</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_SUCCESS_T_5</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>ac0e9c3b06418a586b289a9814be11b59</anchor>
      <arglist>(x, ret, lvl, msg, ast)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_SUCCESS_T_3</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>a82933866a99ed35bcbe92ac8ce87773b</anchor>
      <arglist>(x, ret, ast)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_SUCCESS_T</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>ad96b30c3341a7b5d3b6ccfca95faa4ea</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_SUCCESS_T_NO_ASSERT</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>ad44817449b388b04c52adb0d325d013f</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_SUCCESS_VOID_4</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>a394aa0544b4f5c9731db0e14c0b04c28</anchor>
      <arglist>(x, lvl, msg, ast)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_SUCCESS_VOID_2</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>aa49221c320b4350cc274f78a475f634c</anchor>
      <arglist>(x, ast)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_SUCCESS_VOID</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>a8dfbad38daa9b504f8a3e9abdbec6e26</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_SUCCESS_VOID_NO_ASSERT</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>a66c26261f6d4ef1489565693e77397a2</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_TRUE_5</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>a4a2ed4db1c76cbe297220856d85a348a</anchor>
      <arglist>(x, ret, lvl, msg, ast)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_TRUE_3</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>a3bed960779347552ace0f61c9d05bc04</anchor>
      <arglist>(x, ret, ast)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_TRUE_2</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>a8737899048f9895ae6d5799cc78ef3cd</anchor>
      <arglist>(x, ast)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_TRUE</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>a3dc5059ab2a87bfa4876b29ca6567376</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_TRUE_NO_ASSERT</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>a7702fc672d7c96a60db6e183e29935a6</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_TRUE_T_5</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>a8bf87e0f70b81af575e96224d0bab533</anchor>
      <arglist>(x, ret, lvl, msg, ast)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_TRUE_T_3</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>ad20bf80393ff51c6d4149b6a139f1ed9</anchor>
      <arglist>(x, ret, ast)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_TRUE_T</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>acb13434955ecaff25a715e392d154395</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_TRUE_T_NO_ASSERT</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>a7ff7820d2e3cb687194659c0c15f20b3</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_TRUE_VOID_4</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>adba2a342a5b9749772b2b1d96de1cd13</anchor>
      <arglist>(x, lvl, msg, ast)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_TRUE_VOID_2</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>a3be6ad4a960283a7c5fed24d1d47211b</anchor>
      <arglist>(x, ast)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_TRUE_VOID</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>a798220cc4b67dd310ec6c362531f2a02</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_TRUE_VOID_NO_ASSERT</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>a23da302a5e3a5ad9f79b60045c2fd24e</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_FALSE_5</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>a1b6a9a918385566ef56f5f3bfdb98042</anchor>
      <arglist>(x, ret, lvl, msg, ast)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_FALSE_3</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>ac66b958a2b617c8a7d774f557971f033</anchor>
      <arglist>(x, ret, ast)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_FALSE</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>a7a57f398a574f7027ce3250021608823</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_FALSE_NO_ASSERT</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>a32bc6032a56c23f034f2ee86bb39b72d</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_FALSE_T_5</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>a6b17d847b451bed1787a272b2c7a4398</anchor>
      <arglist>(x, ret, lvl, msg, ast)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_FALSE_T_3</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>adbb14421c85c2c1b1f127d4a82349d8b</anchor>
      <arglist>(x, ret, ast)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_FALSE_T</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>a660d28c672fc8ccf047e92f839046a59</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_FALSE_T_NO_ASSERT</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>a886aca0263c7576e26d38e6703c7e745</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_FALSE_VOID_4</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>ad118f3d95dbdd4cf90fcee969a45998d</anchor>
      <arglist>(x, lvl, msg, ast)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_FALSE_VOID_2</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>aa7c219dc9a17126761d4110bc67c5565</anchor>
      <arglist>(x, ast)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_FALSE_VOID</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>ada3c7191cb32fe578c26a4400bf0198d</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ENSURE_FALSE_VOID_NO_ASSERT</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>a135a8b198da4889c259922dfe8d2a401</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_RETURN_XMRESULT</name>
      <anchorfile>_xm_error_8h.html</anchorfile>
      <anchor>abc07f4f546cbfb927f2f9d0a1d674b59</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>xmresult</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a1503071e7b25b13081f9f478658a1046</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>XM_FAILED_impl</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3969685e7c69e4ed2b8a0a7ab2838abe</anchor>
      <arglist>(xmresult _xmresult)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>XmError.t.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/misc/</path>
    <filename>_xm_error_8t_8h</filename>
    <class kind="class">XmErrorUnitTests</class>
  </compound>
  <compound kind="file">
    <name>XmLog.cpp</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/misc/</path>
    <filename>_xm_log_8cpp</filename>
    <includes id="_xm_log_8h" name="XmLog.h" local="no" imported="no">xmscore/misc/XmLog.h</includes>
    <includes id="_test_tools_8h" name="TestTools.h" local="no" imported="no">xmscore/testing/TestTools.h</includes>
    <includes id="_xm_log_8t_8h" name="XmLog.t.h" local="no" imported="no">xmscore/misc/XmLog.t.h</includes>
    <class kind="class">xms::XmLog::Impl</class>
    <namespace>xmlog</namespace>
    <namespace>xms</namespace>
    <member kind="function">
      <type>std::basic_ostream&lt; CharT, TraitsT &gt; &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespacexmlog.html</anchorfile>
      <anchor>adf50b635bf1e1689ed6355668139e858</anchor>
      <arglist>(std::basic_ostream&lt; CharT, TraitsT &gt; &amp;strm, xmlog::MessageTypeEnum lvl)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_LOG_INLINE_GLOBAL_LOGGER_INIT</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab86edb3135a35aac19595535d700947d</anchor>
      <arglist>(xms_global_log, boost::log::sources::severity_logger_mt&lt; xmlog::MessageTypeEnum &gt;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>iTest_XM_LOG_debug</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0acbea17ab71fd0680dd8c0bbfa0de80</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>iTest_XM_LOG_stackable</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a561ace2fc12a6562ca762ea42fb500f9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>iTest_XM_LOG_gui</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a196857566df5570c425f3982f09a0ce0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static XmLogFilenameCallback</type>
      <name>fg_logFilenameCallback</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aff8502089eb5f522e683cb52ea0a93ae</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>XmLog.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/misc/</path>
    <filename>_xm_log_8h</filename>
    <includes id="_singleton_8h" name="Singleton.h" local="no" imported="no">xmscore/misc/Singleton.h</includes>
    <class kind="class">xms::XmLog</class>
    <namespace>xmlog</namespace>
    <namespace>xms</namespace>
    <member kind="define">
      <type>#define</type>
      <name>XM_LOG</name>
      <anchorfile>_xm_log_8h.html</anchorfile>
      <anchor>a2aa4d2a0a80e464d6acba7f32b13f978</anchor>
      <arglist>(A, B)</arglist>
    </member>
    <member kind="typedef">
      <type>boost::function&lt; std::string()&gt;</type>
      <name>XmLogFilenameCallback</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae3cd81470802b85051b6ef7e4c097535</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; std::pair&lt; xmlog::MessageTypeEnum, std::string &gt; &gt;</type>
      <name>MessageStack</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a854f1e57e755779b900d32077f1fb70c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>MessageTypeEnum</name>
      <anchorfile>namespacexmlog.html</anchorfile>
      <anchor>a7f66c92bb821241cbb29fb07d7bce588</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>info</name>
      <anchorfile>namespacexmlog.html</anchorfile>
      <anchor>a7f66c92bb821241cbb29fb07d7bce588ac70f575410fcc0c690c6e140e609b82d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>warning</name>
      <anchorfile>namespacexmlog.html</anchorfile>
      <anchor>a7f66c92bb821241cbb29fb07d7bce588a6298031baaba1124b5b331212084dcb3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>error</name>
      <anchorfile>namespacexmlog.html</anchorfile>
      <anchor>a7f66c92bb821241cbb29fb07d7bce588a6c90100ca9f6986351a3a437374735c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>debug</name>
      <anchorfile>namespacexmlog.html</anchorfile>
      <anchor>a7f66c92bb821241cbb29fb07d7bce588a42797ff955c778a8a9e21bdd5580a92e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>XmLog.t.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/misc/</path>
    <filename>_xm_log_8t_8h</filename>
    <class kind="class">XmLogUnitTests</class>
  </compound>
  <compound kind="file">
    <name>xmstype.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/misc/</path>
    <filename>xmstype_8h</filename>
    <namespace>xms</namespace>
    <member kind="define">
      <type>#define</type>
      <name>XM_NODATA</name>
      <anchorfile>xmstype_8h.html</anchorfile>
      <anchor>a47f9911b113582ff3a0ed42e083de7b6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_SUCCESS</name>
      <anchorfile>xmstype_8h.html</anchorfile>
      <anchor>a7f96d1229a7678847a8bb97c0d51af50</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_FAILURE</name>
      <anchorfile>xmstype_8h.html</anchorfile>
      <anchor>afceadf3e492e85d81a4f2f28b3d45785</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_ZERO_TOL</name>
      <anchorfile>xmstype_8h.html</anchorfile>
      <anchor>a2a0754bc3b4dbca0eb229608e31a4550</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_PI</name>
      <anchorfile>xmstype_8h.html</anchorfile>
      <anchor>a2fd384675f63eadb4674ab11e5e2cd5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XM_NONE</name>
      <anchorfile>xmstype_8h.html</anchorfile>
      <anchor>a8a1e225f1a26f97086b87346b57b4c16</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>functors.cpp</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/points/</path>
    <filename>functors_8cpp</filename>
    <includes id="functors_8h" name="functors.h" local="no" imported="no">xmscore/points/functors.h</includes>
    <includes id="functors_8t_8h" name="functors.t.h" local="no" imported="no">xmscore/points/functors.t.h</includes>
    <includes id="_test_tools_8h" name="TestTools.h" local="no" imported="no">xmscore/testing/TestTools.h</includes>
    <member kind="typedef">
      <type>std::set&lt; xms::Pt3d, xms::ltPt3d &gt;</type>
      <name>SET_WITH_LTPT3D</name>
      <anchorfile>functors_8cpp.html</anchorfile>
      <anchor>acb1d89c82ac707290b00ada09bc8c896</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>functors.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/points/</path>
    <filename>functors_8h</filename>
    <includes id="pt_8h" name="pt.h" local="no" imported="no">xmscore/points/pt.h</includes>
    <includes id="math_8h" name="math.h" local="no" imported="no">xmscore/math/math.h</includes>
    <class kind="class">xms::ltPt3</class>
    <class kind="class">xms::ltPt3_2D</class>
    <class kind="class">xms::ltPt2</class>
    <namespace>xms</namespace>
    <member kind="typedef">
      <type>ltPt3&lt; double &gt;</type>
      <name>ltPt3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6d6f9950b1bab04111e1f955550f4145</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ltPt3_2D&lt; double &gt;</type>
      <name>ltPt3d_2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9f8a84da20d91174924c5e637a49f133</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ltPt2&lt; double &gt;</type>
      <name>ltPt2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a308bf67d12ecae396921de946d43c489</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Pt2&lt; _T &gt;</type>
      <name>ptTruncate</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>afda18734bb330566478b7c50e405e597</anchor>
      <arglist>(Pt2&lt; _T &gt; const &amp;a_in)</arglist>
    </member>
    <member kind="function">
      <type>Pt3&lt; _T &gt;</type>
      <name>ptTruncate</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a15e2575a62d327a99473f9365ebeadf7</anchor>
      <arglist>(Pt3&lt; _T &gt; const &amp;a_in)</arglist>
    </member>
    <member kind="function">
      <type>Pt4&lt; _T &gt;</type>
      <name>ptTruncate</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab0369aa2588f1c303b03b0319190562c</anchor>
      <arglist>(Pt4&lt; _T &gt; const &amp;a_in)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>functors.t.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/points/</path>
    <filename>functors_8t_8h</filename>
    <class kind="class">FunctorsUnitTests</class>
  </compound>
  <compound kind="file">
    <name>pt.cpp</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/points/</path>
    <filename>pt_8cpp</filename>
    <includes id="pt_8h" name="pt.h" local="no" imported="no">xmscore/points/pt.h</includes>
    <includes id="pt_8t_8h" name="pt.t.h" local="no" imported="no">xmscore/points/pt.t.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>iEQ_EPS</name>
      <anchorfile>pt_8cpp.html</anchorfile>
      <anchor>a1cd890747cc6e8d07dcd4b855ce016d0</anchor>
      <arglist>(A, B, epsilon)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>pt.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/points/</path>
    <filename>pt_8h</filename>
    <includes id="ptsfwd_8h" name="ptsfwd.h" local="no" imported="no">xmscore/points/ptsfwd.h</includes>
    <class kind="class">xms::Pt2</class>
    <class kind="class">xms::Pt3</class>
    <class kind="class">xms::Pt4</class>
    <namespace>xms</namespace>
    <member kind="function">
      <type>Pt3&lt; T &gt;</type>
      <name>operator*</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a631780f1735d5928d3613a6cba3c7f66</anchor>
      <arglist>(int a, const Pt3&lt; T &gt; &amp;pt)</arglist>
    </member>
    <member kind="function">
      <type>Pt3&lt; T &gt;</type>
      <name>operator*</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>abab9e54c65c43c4da48f3609d6a82f42</anchor>
      <arglist>(float a, const Pt3&lt; T &gt; &amp;pt)</arglist>
    </member>
    <member kind="function">
      <type>Pt3&lt; T &gt;</type>
      <name>operator*</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad616ca2ecb89f938799154b405ea66a7</anchor>
      <arglist>(double a, const Pt3&lt; T &gt; &amp;pt)</arglist>
    </member>
    <member kind="function">
      <type>_To &amp;</type>
      <name>Pt3Convert</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a659e78a80e43ed5eddb137738c8bba28</anchor>
      <arglist>(const _From &amp;a_from, _To &amp;a_to)</arglist>
    </member>
    <member kind="function">
      <type>std::basic_ostream&lt; charT, traits &gt; &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac664d3911e8b952aedb47b8aa7fcbe92</anchor>
      <arglist>(std::basic_ostream&lt; charT, traits &gt; &amp;strm, const Pt2&lt; T &gt; &amp;a_pt)</arglist>
    </member>
    <member kind="function">
      <type>std::basic_istream&lt; charT, traits &gt; &amp;</type>
      <name>operator&gt;&gt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab144710d1aa9fda03fd1443dbe58d9b5</anchor>
      <arglist>(std::basic_istream&lt; charT, traits &gt; &amp;strm, Pt2&lt; T &gt; &amp;a_pt)</arglist>
    </member>
    <member kind="function">
      <type>std::basic_ostream&lt; charT, traits &gt; &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac2e166377153c8720707026ead37f326</anchor>
      <arglist>(std::basic_ostream&lt; charT, traits &gt; &amp;strm, const Pt3&lt; T &gt; &amp;a_pt)</arglist>
    </member>
    <member kind="function">
      <type>std::basic_istream&lt; charT, traits &gt; &amp;</type>
      <name>operator&gt;&gt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5bd13d3b7d8191820833e7cba519f7d0</anchor>
      <arglist>(std::basic_istream&lt; charT, traits &gt; &amp;strm, Pt3&lt; T &gt; &amp;a_pt)</arglist>
    </member>
    <member kind="function">
      <type>std::basic_ostream&lt; charT, traits &gt; &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a371ec7fc6076bc607aac9ad86cabd3e6</anchor>
      <arglist>(std::basic_ostream&lt; charT, traits &gt; &amp;strm, const Pt4&lt; T &gt; &amp;a_pt)</arglist>
    </member>
    <member kind="function">
      <type>std::basic_istream&lt; charT, traits &gt; &amp;</type>
      <name>operator&gt;&gt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a76c9fa0b148a3a01b927943faad3b7b9</anchor>
      <arglist>(std::basic_istream&lt; charT, traits &gt; &amp;strm, Pt4&lt; T &gt; &amp;a_pt)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>pt.t.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/points/</path>
    <filename>pt_8t_8h</filename>
    <class kind="class">PtUnitTests</class>
  </compound>
  <compound kind="file">
    <name>ptsfwd.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/points/</path>
    <filename>ptsfwd_8h</filename>
    <class kind="class">xms::Pt2</class>
    <class kind="class">xms::Pt3</class>
    <class kind="class">xms::Pt4</class>
    <namespace>xms</namespace>
    <member kind="typedef">
      <type>Pt2&lt; int &gt;</type>
      <name>Pt2i</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a518c7b2b0bcae0bdcc73126e85c83047</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Pt2&lt; float &gt;</type>
      <name>Pt2f</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9f994e9ae9086aa1fe47d87a8f8a10c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Pt2&lt; double &gt;</type>
      <name>Pt2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a744e494df03812a8bf92b5383bb48cef</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Pt3&lt; int &gt;</type>
      <name>Pt3i</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af2ee555d81375541d81fb08519bc7e3c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Pt3&lt; float &gt;</type>
      <name>Pt3f</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab48f0df70ce7acac4413e2062a5a97c2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Pt3&lt; double &gt;</type>
      <name>Pt3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a33ae0c78e599c46ba59bce7f2b32d7ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Pt4&lt; int &gt;</type>
      <name>Pt4i</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0950f9ab66e0ebdd36bb554f6421516d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Pt4&lt; float &gt;</type>
      <name>Pt4f</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aa8bce394e573e9cb3aee50e088a829ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Pt4&lt; double &gt;</type>
      <name>Pt4d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>afefc2ac7e0e4006c5984dcfb74a4f8b2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>misc_py.cpp</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/python/misc/</path>
    <filename>misc__py_8cpp</filename>
    <includes id="misc__py_8h" name="misc_py.h" local="no" imported="no">xmscore/python/misc/misc_py.h</includes>
  </compound>
  <compound kind="file">
    <name>misc_py.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/python/misc/</path>
    <filename>misc__py_8h</filename>
  </compound>
  <compound kind="file">
    <name>observer_py.cpp</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/python/misc/</path>
    <filename>observer__py_8cpp</filename>
    <includes id="misc__py_8h" name="misc_py.h" local="no" imported="no">xmscore/python/misc/misc_py.h</includes>
    <includes id="_public_observer_8h" name="PublicObserver.h" local="no" imported="no">xmscore/python/misc/PublicObserver.h</includes>
    <includes id="_py_observer_8h" name="PyObserver.h" local="no" imported="no">xmscore/python/misc/PyObserver.h</includes>
  </compound>
  <compound kind="file">
    <name>PublicObserver.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/python/misc/</path>
    <filename>_public_observer_8h</filename>
    <includes id="_observer_8h" name="Observer.h" local="no" imported="no">xmscore/misc/Observer.h</includes>
    <class kind="class">xms::PublicObserver</class>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>PyObserver.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/python/misc/</path>
    <filename>_py_observer_8h</filename>
    <includes id="_public_observer_8h" name="PublicObserver.h" local="no" imported="no">xmscore/python/misc/PublicObserver.h</includes>
    <class kind="class">PyObserver</class>
  </compound>
  <compound kind="file">
    <name>PyUtils.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/python/misc/</path>
    <filename>_py_utils_8h</filename>
    <includes id="_dyn_bitset_8h" name="DynBitset.h" local="no" imported="no">xmscore/misc/DynBitset.h</includes>
    <includes id="ptsfwd_8h" name="ptsfwd.h" local="no" imported="no">xmscore/points/ptsfwd.h</includes>
    <includes id="vector_8h" name="vector.h" local="no" imported="no">xmscore/stl/vector.h</includes>
    <namespace>xms</namespace>
    <member kind="function">
      <type>Pt3d</type>
      <name>Pt3dFromPyIter</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af8bd6c40daeb861c5adaf92f11abdf56</anchor>
      <arglist>(const py::tuple &amp;pt)</arglist>
    </member>
    <member kind="function">
      <type>py::tuple</type>
      <name>PyIterFromPt3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8d24b1f36c9883e275f3d151f757bcf8</anchor>
      <arglist>(const Pt3d &amp;pt)</arglist>
    </member>
    <member kind="function">
      <type>boost::shared_ptr&lt; VecPt3d &gt;</type>
      <name>VecPt3dFromPyIter</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a43267849a6908be20246a8237928dcbf</anchor>
      <arglist>(const py::iterable &amp;pts)</arglist>
    </member>
    <member kind="function">
      <type>py::iterable</type>
      <name>PyIterFromVecPt3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8e892242a41a91506ce59befc5ca2f84</anchor>
      <arglist>(const VecPt3d &amp;pts)</arglist>
    </member>
    <member kind="function">
      <type>boost::shared_ptr&lt; VecPt3d2d &gt;</type>
      <name>VecPt3d2dFromPyIter</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8341d3f2b243f05d88a293f90a0febbb</anchor>
      <arglist>(const py::iterable &amp;pts)</arglist>
    </member>
    <member kind="function">
      <type>py::iterable</type>
      <name>PyIterFromVecPt3d2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3e5f96042bb96b842510d6199ce14b25</anchor>
      <arglist>(const VecPt3d2d &amp;pts)</arglist>
    </member>
    <member kind="function">
      <type>boost::shared_ptr&lt; VecInt2d &gt;</type>
      <name>VecInt2dFromPyIter</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aa4c0bf973be9e1f13c1f793eff468b37</anchor>
      <arglist>(const py::iterable &amp;int2d)</arglist>
    </member>
    <member kind="function">
      <type>py::iterable</type>
      <name>PyIterFromVecInt2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0a1a01df38749fc3086ebfc93d8598da</anchor>
      <arglist>(const VecInt2d &amp;int2d)</arglist>
    </member>
    <member kind="function">
      <type>boost::shared_ptr&lt; VecInt &gt;</type>
      <name>VecIntFromPyIter</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3685fbd2c82bfe5ae4ec3e1e978d8d92</anchor>
      <arglist>(const py::iterable &amp;ints)</arglist>
    </member>
    <member kind="function">
      <type>py::iterable</type>
      <name>PyIterFromVecInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a916a7b311cc18c5c1c9720be157b3d0b</anchor>
      <arglist>(const VecInt &amp;ints, bool numpy)</arglist>
    </member>
    <member kind="function">
      <type>boost::shared_ptr&lt; VecDbl &gt;</type>
      <name>VecDblFromPyIter</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab5fd3653a6331570a61ff881917641ca</anchor>
      <arglist>(const py::iterable &amp;dbls)</arglist>
    </member>
    <member kind="function">
      <type>py::iterable</type>
      <name>PyIterFromVecDbl</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4f49d28bec256c7554c7546ff58df20a</anchor>
      <arglist>(const VecDbl &amp;dbls, bool numpy)</arglist>
    </member>
    <member kind="function">
      <type>boost::shared_ptr&lt; VecFlt &gt;</type>
      <name>VecFltFromPyIter</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8bddf97e8dc7cb2d2bcd1df5e477efb1</anchor>
      <arglist>(const py::iterable &amp;flts)</arglist>
    </member>
    <member kind="function">
      <type>py::iterable</type>
      <name>PyIterFromVecFlt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a7b285c38273bed1a3d6f3af5d3cbf357</anchor>
      <arglist>(const VecFlt &amp;flts, bool numpy)</arglist>
    </member>
    <member kind="function">
      <type>DynBitset</type>
      <name>DynamicBitsetFromPyIter</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a49bb2e3cc528e336292b521275482042</anchor>
      <arglist>(const py::iterable &amp;bitset)</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; int, int &gt;</type>
      <name>IntPairFromPyIter</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad1c4eab1d9f098f293e8205a2c372788</anchor>
      <arglist>(const py::iterable &amp;intpair)</arglist>
    </member>
    <member kind="function">
      <type>py::iterable</type>
      <name>PyIterFromIntPair</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>abb18038767a6eef784fe157b79ab5bd3</anchor>
      <arglist>(const std::pair&lt; int, int &gt; &amp;intpair)</arglist>
    </member>
    <member kind="function">
      <type>boost::shared_ptr&lt; std::vector&lt; std::pair&lt; int, int &gt; &gt; &gt;</type>
      <name>VecIntPairFromPyIter</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>afcdebdd67720da722a796de78c531f2e</anchor>
      <arglist>(const py::iterable &amp;intpairs)</arglist>
    </member>
    <member kind="function">
      <type>py::iterable</type>
      <name>PyIterFromVecIntPair</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a90078769bd51c076d22a3911983acaf6</anchor>
      <arglist>(const std::vector&lt; std::pair&lt; int, int &gt;&gt; &amp;intpairs)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>xmscore_py.cpp</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/python/</path>
    <filename>xmscore__py_8cpp</filename>
    <includes id="misc__py_8h" name="misc_py.h" local="no" imported="no">xmscore/python/misc/misc_py.h</includes>
  </compound>
  <compound kind="file">
    <name>deque.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/stl/</path>
    <filename>deque_8h</filename>
    <includes id="ptsfwd_8h" name="ptsfwd.h" local="no" imported="no">xmscore/points/ptsfwd.h</includes>
    <namespace>xms</namespace>
    <member kind="typedef">
      <type>std::deque&lt; Pt2d &gt;</type>
      <name>DEQ_PT2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad17ebff442a5af50e93b027dc76fac07</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::deque&lt; Pt2d &gt;</type>
      <name>DeqPt2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab075c6283191e8574d5b982e7a059e03</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>hash.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/stl/</path>
    <filename>hash_8h</filename>
    <namespace>xms</namespace>
    <member kind="typedef">
      <type>stdext::hash_map&lt; std::string, std::string &gt;</type>
      <name>HASH_S_S</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a56e54e0912307d4de71a4d78d8d68278</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>stdext::hash_map&lt; int, std::string &gt;</type>
      <name>HASH_I_S</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>acaab4614cdb61c53069a10e3e3900992</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>stdext::hash_map&lt; std::string, std::string &gt;</type>
      <name>HashStrStr</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aed890677ebeb23e366bf88d576a1fa8d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>stdext::hash_map&lt; int, std::string &gt;</type>
      <name>HashIntStr</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a70bd6170c9e2680843e379eb968b43c5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>list.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/stl/</path>
    <filename>list_8h</filename>
    <namespace>xms</namespace>
    <member kind="typedef">
      <type>std::list&lt; Pt2d &gt;</type>
      <name>LIST_MP2</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a752b01cd2f5da0f0666c9b8d618d3e73</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::list&lt; Pt2d &gt;</type>
      <name>ListPt2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae9fd3d8a0d241b1da7cf2f6b22e13fb7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>map.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/stl/</path>
    <filename>map_8h</filename>
    <includes id="ptsfwd_8h" name="ptsfwd.h" local="no" imported="no">xmscore/points/ptsfwd.h</includes>
    <includes id="vector_8h" name="vector.h" local="no" imported="no">xmscore/stl/vector.h</includes>
    <includes id="set_8h" name="set.h" local="no" imported="no">xmscore/stl/set.h</includes>
    <namespace>xms</namespace>
    <member kind="typedef">
      <type>std::map&lt; double, double &gt;</type>
      <name>MapDblDbl</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a96319792209e6107cd0c7fb2405e838d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; double, int &gt;</type>
      <name>MapDblInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a760083c970c1c8999eba9c675e18fe0f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; double, std::string &gt;</type>
      <name>MapDblStr</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>adcebdd9d2d0a5791feee0022ed6615e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, bool &gt;</type>
      <name>MapIntBool</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8873858f58439ef2542640d460f2f2ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, double &gt;</type>
      <name>MapIntDbl</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a320d3c4b7bd375eb56ba1a48eb9531aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, float &gt;</type>
      <name>MapIntFlt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5a8fd93dc68064b65820a0673f8c470d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, float ** &gt;</type>
      <name>MapIntFlt2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a13a075958351f2bd9c53dc5e071875c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, int &gt;</type>
      <name>MapIntInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae04b2b1c55d9731d0a5cb1df2e2e45fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, SetInt &gt;</type>
      <name>MapIntSetInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aaf8f06591bf3cfa69ccdbdebb689d435</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, std::string &gt;</type>
      <name>MapIntStr</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a42e244f0cc8aaea1c3a5808c502090b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, Pt3d &gt;</type>
      <name>MapIntPt3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a96099a3e91d4511fbb214f2aee566ebe</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, VecDbl &gt;</type>
      <name>MapIntVecDbl</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>acfd1315a0883ffe944d1f6f065e11d77</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, VecFlt &gt;</type>
      <name>MapIntVecFlt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6a6a53a2f851e3ddae669175cb634332</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, VecFlt2d &gt;</type>
      <name>MapIntVecFlt2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4fc6842b97a35032224a67a3cf147449</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, VecInt &gt;</type>
      <name>MapIntVecInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af48f45bc066cf776edc51b449195b6f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, MapIntDbl &gt;</type>
      <name>MapIntMapIntDbl</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a86f52b0704e63cda25c422352c7096ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, MapIntFlt &gt;</type>
      <name>MapIntMapIntFlt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a29a10625efb925d32ccf1bb89e9a8d81</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, MapIntInt &gt;</type>
      <name>MapIntMapIntInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aa093012c3a6b357d08907f5039abcbfa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; Pt3d, int &gt;</type>
      <name>MapPt3dInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5de588db3d596532fe6b9df5703fc93d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; std::string, double &gt;</type>
      <name>MapStrDbl</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8c3c2d9bcbe0e5bc777263dc39a1b5f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; std::string, int &gt;</type>
      <name>MapStrInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3237d9d174ce16a2443db939380ce83d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; std::string, MapIntDbl &gt;</type>
      <name>MapStrMapIntDbl</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a34bedebf9a1985bdf4424fb9f2beff93</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; std::string, std::string &gt;</type>
      <name>MapStrStr</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4a10c2e6f4da3c31779497493b88e086</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; std::string, VecStr &gt;</type>
      <name>MapStrVecStr</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac3b01f9f75e31dff0c2dd37d68409b02</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::multimap&lt; bool, int &gt;</type>
      <name>MmapBoolInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad2d0318b5dbae330617f569db3213c82</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::multimap&lt; double, int &gt;</type>
      <name>MmapDblInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a96e869281d10830ca3935720cbaba8dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::multimap&lt; int, int &gt;</type>
      <name>MmapIntInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>acb4ccb3448b7899772bd48d7fff52a1c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::multimap&lt; std::string, int &gt;</type>
      <name>MmapStrInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a663bb1c6bd93293cf091ab7fdff684c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a82b65663cc847bc0db8ac4c0930406fb</anchor>
      <arglist>(std::ostream &amp;a_output, const std::map&lt; _T, _U &gt; &amp;a_value)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a89dc698eb82bff44b24c6a00427aeedb</anchor>
      <arglist>(std::ostream &amp;a_output, const std::multimap&lt; _T, _U &gt; &amp;a_value)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>set.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/stl/</path>
    <filename>set_8h</filename>
    <includes id="ptsfwd_8h" name="ptsfwd.h" local="no" imported="no">xmscore/points/ptsfwd.h</includes>
    <namespace>xms</namespace>
    <member kind="typedef">
      <type>std::set&lt; Pt2d &gt;</type>
      <name>SetPt2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>abe338c6aad290b9e63a796b089580a2d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::set&lt; Pt3d &gt;</type>
      <name>SetPt3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ace0c4bf93aa2fbca1de7fdba9e31c054</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::set&lt; Pt4d &gt;</type>
      <name>SetPt4d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a131d97f1b3c7a688577d2ac1d7206f1f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::set&lt; size_t &gt;</type>
      <name>SetSizet</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8701e9932125a2152d0ffc5d6b301d55</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::set&lt; int &gt;</type>
      <name>SetInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af6291e795c0018d80c22e2bd9bc2888c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::set&lt; int64_t &gt;</type>
      <name>SetInt64</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aeba38cc9ea2c11044a95c0eba06a9bb9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::set&lt; float &gt;</type>
      <name>SetFlt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>abea86738bccb0a9444cedb046c9b74a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::set&lt; double &gt;</type>
      <name>SetDbl</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab68506e4a18b8a7de878eb9181cfda56</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::set&lt; std::string &gt;</type>
      <name>SetStr</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a33394672ae51929bc113aebffe9069d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a02ae6e1c76aef482f18d88a992ba0ad9</anchor>
      <arglist>(std::ostream &amp;a_output, const std::set&lt; _T &gt; &amp;a_value)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>utility.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/stl/</path>
    <filename>utility_8h</filename>
    <namespace>xms</namespace>
    <member kind="typedef">
      <type>std::pair&lt; int, int &gt;</type>
      <name>PAIR_I_I</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad9330a096ca1941af220275e240016d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac1d111686a755d63ff7ff55c80450e9e</anchor>
      <arglist>(std::ostream &amp;a_output, const std::pair&lt; _T, _U &gt; &amp;a_value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>VecToStream</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9be33abf1221de1679a4ff237b549efb</anchor>
      <arglist>(std::stringstream &amp;a_ss, const T &amp;a_v, std::string a_label)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>vector.cpp</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/stl/</path>
    <filename>vector_8cpp</filename>
    <includes id="vector_8h" name="vector.h" local="no" imported="no">xmscore/stl/vector.h</includes>
  </compound>
  <compound kind="file">
    <name>vector.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/stl/</path>
    <filename>vector_8h</filename>
    <includes id="pt_8h" name="pt.h" local="no" imported="no">xmscore/points/pt.h</includes>
    <namespace>xms</namespace>
    <member kind="typedef">
      <type>std::vector&lt; bool &gt;</type>
      <name>VecBool</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a050c6b4a3040009b4bf6fc7f73714c9f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; char &gt;</type>
      <name>VecChar</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>afd4eedad4cc93746d505257ad086bd53</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; unsigned char &gt;</type>
      <name>VecUchar</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a929375fccc7c71c456bc6e1ef22909b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; double &gt;</type>
      <name>VecDbl</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5de59c68ff16d81cb2a429173f3a2fa5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; float &gt;</type>
      <name>VecFlt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a386622729e9b0e733d6eaac4e0e711c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; int &gt;</type>
      <name>VecInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad81e1ef6499bc0e65df973717a1e2fbb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; unsigned int &gt;</type>
      <name>VecUint</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a90633b22271b64f73e832ef9a023c282</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; short &gt;</type>
      <name>VecShort</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0583923a141e14a792e63d480a4927d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; std::string &gt;</type>
      <name>VecStr</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aec782765108bad312607f9ddcc90eb62</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; void * &gt;</type>
      <name>VecVoid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a63374baf974e2f7d75033f9866214ea4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; std::size_t &gt;</type>
      <name>VecSizet</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a7b87d9c3ada9a6c1d3684a09247fbbeb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecFlt &gt;</type>
      <name>VecFlt2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a7f783acf77704ab019a31d867e2548ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecInt &gt;</type>
      <name>VecInt2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a91ad569308b76393ca27c1270a637d9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecDbl &gt;</type>
      <name>VecDbl2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a139b3b5faf4391ffae6815bd68d7d68d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecStr &gt;</type>
      <name>VecStr2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aa5e84be6ceaa52d7140282252bf8fe4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecSizet &gt;</type>
      <name>VecSizet2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a91de3187e7a3c1cd3e0ecfb21a1782c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecFlt2d &gt;</type>
      <name>VecFlt3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aeac46db5bf5f0ab49abef27f808d8464</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecInt2d &gt;</type>
      <name>VecInt3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aac1c2f8265a306e691d4ab1ac2300f2b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecDbl2d &gt;</type>
      <name>VecDbl3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>adb29b07af3808422651d57e2de63afef</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecStr2d &gt;</type>
      <name>VecStr3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a13ddd673c4b345fffc41cd95807d429a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecDbl3d &gt;</type>
      <name>VecDbl4d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a7b7add4774d4dfdd6233a6d5b8c3f3f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecFlt3d &gt;</type>
      <name>VecFlt4d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a54c7589307bbbfc081e02e0114c1eff5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; Pt4d &gt;</type>
      <name>VecPt4d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>abea17c4af0781cb9a16dd7970a73fbfc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; Pt3d &gt;</type>
      <name>VecPt3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0dc29604ee813731d584232b63f54922</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; Pt3f &gt;</type>
      <name>VecPt3f</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a17a077741174f8fc1e40e8513983a46b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; Pt2d &gt;</type>
      <name>VecPt2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af62f55649566e3c0cae2c9547031c5ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; Pt2f &gt;</type>
      <name>VecPt2f</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>acaa0f15a13b3ed7a9a6c6efe852f0637</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; Pt2i &gt;</type>
      <name>VecPt2i</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4981187cb84e75c3a25e19e3fe0a6f73</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecPt2d &gt;</type>
      <name>VecPt2d2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aab85a4b0741ae0758048122842ddfc49</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecPt2f &gt;</type>
      <name>VecPt2f2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac49e25a9f1734d84a0c6ad51b5aedf9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecPt3d &gt;</type>
      <name>VecPt3d2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a1b0ce86e91b176c54f0f122476873c75</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecPt3f &gt;</type>
      <name>VecPt3f2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a2256d4c8e906d3ed11857188957b2154</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecPt3d2d &gt;</type>
      <name>VecPt3d3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3baed22b50d99fef3f3bc78c99eaf26f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad55f289cf34d6e2f8baad6daf5b566f4</anchor>
      <arglist>(std::ostream &amp;a_output, const std::vector&lt; _T &gt; &amp;a_value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stShrinkCapacity</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>adb9ba9ba787e4ecd0017e0b2b149c564</anchor>
      <arglist>(std::vector&lt; T &gt; &amp;v)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>TestTools.cpp</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/testing/</path>
    <filename>_test_tools_8cpp</filename>
    <includes id="_test_tools_8h" name="TestTools.h" local="no" imported="no">xmscore/testing/TestTools.h</includes>
    <includes id="environment_8h" name="environment.h" local="no" imported="no">xmscore/misc/environment.h</includes>
    <includes id="_xm_log_8h" name="XmLog.h" local="no" imported="no">xmscore/misc/XmLog.h</includes>
    <namespace>xms</namespace>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>ttDefaultXmsngTestPath</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aea25a4299c927c1733790a4dc3bc0882</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>ttGetXmsngTestPath</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>acddaa287c080f4199d840c9ca3e29f23</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ttByPassMessages</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9a6679c474ce3bc806395023736dcfe6</anchor>
      <arglist>(int a_defaultChoice)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ttSkippingMessages</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac8e299c3d55effb9358f87e945692da4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ttByPassDefault</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad062784654592a88d525970efcc8d914</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ttClearSkippingMessages</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aca82daee4102af38576458952c71be04</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ETestMessagingState &amp;</type>
      <name>ttTestMessagingState</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a99d430c07eede7029ba975abe116b5e9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ttCheckXmLogForEachTest</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a89a1187517e055debbd1f536e50f0a03</anchor>
      <arglist>(bool a_setting)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ttCheckXmLogForEachTest</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0af2260e97dd0a9508b272401bc13333</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ttAssertStackedErrors</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac619b9bd692506c31fba6febdd34136e</anchor>
      <arglist>(const char *a_file, int a_line, const std::string &amp;a_expected)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ttGetTestFilePaths</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a21c6cbf8cb7289e3ac5adf2c02f3db62</anchor>
      <arglist>(const std::string &amp;a_path, const std::string &amp;a_fileBase, const std::string &amp;a_extension, std::string &amp;a_baseFilePath, std::string &amp;a_outFilePath)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ttTextFilesEqual</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a326ac713f6a09e5de3b4afdb3a8f0bd5</anchor>
      <arglist>(const std::string &amp;a_file1, const std::string &amp;a_file2, std::string &amp;a_message)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ttTextFilesEqual</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af756be86cffac9304409c60bba5dbafd</anchor>
      <arglist>(const std::string &amp;a_srcFile, unsigned a_line, const std::string &amp;a_file1, const std::string &amp;a_file2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ttStreamsEqual</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab4a12bdfe2030df3dafdd066679656d1</anchor>
      <arglist>(const std::string &amp;a_src, unsigned int a_line, std::istream &amp;a_strm1, std::istream &amp;a_strm2)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>TestTools.h</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/testing/</path>
    <filename>_test_tools_8h</filename>
    <includes id="utility_8h" name="utility.h" local="no" imported="no">xmscore/stl/utility.h</includes>
    <class kind="class">xms::ETestMessagingState</class>
    <namespace>xms</namespace>
    <member kind="define">
      <type>#define</type>
      <name>_TS_ASSERT_EQUALS_AVEC</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>a9333b05e6f5ab593b58a4f18ad9a9ed0</anchor>
      <arglist>(f, l, expected, length, actual)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TS_ASSERT_EQUALS_AVEC</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>abdb22f26bd303255f4446269a73cd1ae</anchor>
      <arglist>(expected, length, actual)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_TS_ASSERT_DELTA_VEC</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>a08a9e0b4decb6f8b9b4beb5bcf9ed8e8</anchor>
      <arglist>(f, l, a, b, delta)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TS_ASSERT_DELTA_VEC</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>aa093335ed24e9478f11c0ab037a21597</anchor>
      <arglist>(a, b, delta)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_TS_ASSERT_DELTA_VEC2D</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>a1fbf6e5846b38f96866452d2249dbbcf</anchor>
      <arglist>(f, l, a, b, delta)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TS_ASSERT_DELTA_VEC2D</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>ac15f801474fcb45d21284de5265b351d</anchor>
      <arglist>(a, b, delta)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_TS_ASSERT_EQUALS_VEC2D</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>ae55d85d8b1c484f41b27cf8c13133a39</anchor>
      <arglist>(f, l, expected, actual)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TS_ASSERT_EQUALS_VEC2D</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>a035dbfd193c794bbdf2c916aaaf8ec88</anchor>
      <arglist>(expected, actual)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_TS_ASSERT_DELTA_VECPT3D</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>a161e4d96aba9bdcb92b3b970d5e80717</anchor>
      <arglist>(f, l, a, b, delta)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TS_ASSERT_DELTA_VECPT3D</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>ad074895a54cf874aed416e323758f355</anchor>
      <arglist>(a, b, delta)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TS_ASSERT_DELTA_VEC_MP3</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>ae6993be421133bed244cbf5876690747</anchor>
      <arglist>(a, b, delta)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_TS_ASSERT_DELTA_VECPT2D</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>a62afee6ecfd200a6d10f9e3739624633</anchor>
      <arglist>(f, l, a, b, delta)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TS_ASSERT_DELTA_VECPT2D</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>a7d5f328388c2034d6fdcd47bb5d64759</anchor>
      <arglist>(a, b, delta)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TS_ASSERT_DELTA_VEC_MP2</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>a19ff19a981397a8a431689b23f0c690f</anchor>
      <arglist>(a, b, delta)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_TS_ASSERT_DELTA_PT3D</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>aed62aaca51fceea372f299053edc30f9</anchor>
      <arglist>(f, l, a, b, delta)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_TS_ASSERT_DELTA_PT2D</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>a9b413493a3f5104ffc246199ae30cde3</anchor>
      <arglist>(f, l, a, b, delta)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TS_ASSERT_DELTA_PT3D</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>a8cf38238ae1360b955b35555180bd5bb</anchor>
      <arglist>(a, b, delta)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TS_ASSERT_DELTA_PT2D</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>ab9339b9ec3adf37f908a5086db888e37</anchor>
      <arglist>(a, b, delta)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_TS_ASSERT_TXT_FILES_EQUAL</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>abf2b287d20d6ffc0af6a56d1cae4018c</anchor>
      <arglist>(f, l, a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TS_ASSERT_TXT_FILES_EQUAL</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>a910e81903f66d29dc334d1ed7c57ca5d</anchor>
      <arglist>(a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_TS_ASSERT_STREAMS_EQUAL</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>a703cbe5475f8db8f86e845a9a6eb0382</anchor>
      <arglist>(f, l, a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TS_ASSERT_STREAMS_EQUAL</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>a0032c4402f5177fec5fb7d0250fde9a9</anchor>
      <arglist>(a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_TS_ASSERT_EQUALS_VEC</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>ae2431bc820a697eba3c4bfb00cd5fb97</anchor>
      <arglist>(f, l, a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TS_ASSERT_EQUALS_VEC</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>a320ba70a42230e622cff58c5b4922cac</anchor>
      <arglist>(a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_TS_REQUIRE_NOT_NULL</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>af928019c8c844648d2780d61f8ffcfb6</anchor>
      <arglist>(f, l, pointer)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TS_REQUIRE_NOT_NULL</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>a28b7afe91f1ad45ab31f57e7d5051b80</anchor>
      <arglist>(pointer)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_TS_ASSERT_STACKED_ERRORS</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>aa426ce439ef77a8fa23e524a24a53958</anchor>
      <arglist>(f, l, expected)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TS_ASSERT_STACKED_ERRORS</name>
      <anchorfile>_test_tools_8h.html</anchorfile>
      <anchor>a28a882a826cd93120c960b1b8ec18503</anchor>
      <arglist>(expected)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ttEqualWithinTolerance</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab2413ef9370a53971fba0302d9899c84</anchor>
      <arglist>(_T A, _U B, _V tolerance)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ttAssertDeltaVec</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a60ce526c07fa6f1fb54bf3713ae93c9a</anchor>
      <arglist>(const char *f, unsigned l, const std::vector&lt; T &gt; &amp;a, const std::vector&lt; T &gt; &amp;b, U delta)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ttAssertDeltaVec2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae98e466f8d6113a5361c16aa586427e6</anchor>
      <arglist>(const char *f, unsigned l, const std::vector&lt; std::vector&lt; T &gt; &gt; &amp;a, const std::vector&lt; std::vector&lt; T &gt; &gt; &amp;b, U delta)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ttAssertEqualsAVec</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aeb9eb5d8ce05366856464f6258e84f85</anchor>
      <arglist>(const char *a_file, int a_line, const T *a_expected, size_t a_expectedLength, const std::vector&lt; T &gt; &amp;a_actual)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ttAssertEqualsVec2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4dbfdd1e82e9a97582b148fbeba175e4</anchor>
      <arglist>(const char *f, unsigned l, const std::vector&lt; std::vector&lt; T &gt; &gt; &amp;a, const std::vector&lt; std::vector&lt; T &gt; &gt; &amp;b)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FunctorsUnitTests</name>
    <filename>class_functors_unit_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>TestIt</name>
      <anchorfile>class_functors_unit_tests.html</anchorfile>
      <anchor>a7251c5b6b4ea9ae73b1d8ffe1e234adf</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MathUnitTests</name>
    <filename>class_math_unit_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>TestIt</name>
      <anchorfile>class_math_unit_tests.html</anchorfile>
      <anchor>ad5f6ba6a9ccdcb0d42db9ddc6192bda5</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MockMesher</name>
    <filename>class_mock_mesher.html</filename>
    <member kind="function">
      <type>void</type>
      <name>SetObserver</name>
      <anchorfile>class_mock_mesher.html</anchorfile>
      <anchor>aeac68bcbce1b9c33aeffb497dd7b5901</anchor>
      <arglist>(BSHP&lt; xms::Observer &gt; a_)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>WaitForNextTenthSecond</name>
      <anchorfile>class_mock_mesher.html</anchorfile>
      <anchor>aa79c8ee5f4c3546c0c8fadd89ab85044</anchor>
      <arglist>(boost::timer::cpu_timer &amp;a_timer, int &amp;a_count)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PretendMeshing</name>
      <anchorfile>class_mock_mesher.html</anchorfile>
      <anchor>af90fd308a879f30505a9e7a7cae521bf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>BSHP&lt; xms::Observer &gt;</type>
      <name>m_prog</name>
      <anchorfile>class_mock_mesher.html</anchorfile>
      <anchor>ad20d9d1963a422214083cc34ab511fe6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MockObserver</name>
    <filename>class_mock_observer.html</filename>
    <base>xms::Observer</base>
    <member kind="variable">
      <type>double</type>
      <name>m_percentComplete</name>
      <anchorfile>class_mock_observer.html</anchorfile>
      <anchor>af0a06385a1f399ca99490140fe14dd1b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>m_remainingSeconds</name>
      <anchorfile>class_mock_observer.html</anchorfile>
      <anchor>aae5ef68dd0fb8afc8c298328a79ec4ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>m_elapsedSeconds</name>
      <anchorfile>class_mock_observer.html</anchorfile>
      <anchor>afc3ef4e691059d420277e39e669866c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::stringstream</type>
      <name>m_info</name>
      <anchorfile>class_mock_observer.html</anchorfile>
      <anchor>abd027f414e13a3fdb149f76d5be2e4d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual void</type>
      <name>OnProgressStatus</name>
      <anchorfile>class_mock_observer.html</anchorfile>
      <anchor>a508a232c3577cabe9add637c7e735408</anchor>
      <arglist>(double a_percentComplete) override</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual void</type>
      <name>OnBeginOperationString</name>
      <anchorfile>class_mock_observer.html</anchorfile>
      <anchor>a61e1664593f8473eb45dad4a312116df</anchor>
      <arglist>(const std::string &amp;a_operation) override</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual void</type>
      <name>TimeElapsedInSeconds</name>
      <anchorfile>class_mock_observer.html</anchorfile>
      <anchor>a90d9553adba545bc8e45378d3a57b2e1</anchor>
      <arglist>(double a_elapsedSeconds) override</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual void</type>
      <name>TimeRemainingInSeconds</name>
      <anchorfile>class_mock_observer.html</anchorfile>
      <anchor>a08f150ac9a3c517c99de3fcd40e382d0</anchor>
      <arglist>(double a_secondsRemaining) override</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ProgressStatus</name>
      <anchorfile>classxms_1_1_observer.html</anchorfile>
      <anchor>ac53cde5a326843717b57e49767ff5be4</anchor>
      <arglist>(double a_percentComplete)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>BeginOperationString</name>
      <anchorfile>classxms_1_1_observer.html</anchorfile>
      <anchor>a70a1cf0b6f4ab3bb533dda17767abf3f</anchor>
      <arglist>(const std::string &amp;a_operation)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EndOperation</name>
      <anchorfile>classxms_1_1_observer.html</anchorfile>
      <anchor>a6ab39e266617c93fb0720f23efa723e0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>UpdateMessage</name>
      <anchorfile>classxms_1_1_observer.html</anchorfile>
      <anchor>afb06a8401e959a1edc51a4b4f9f4107b</anchor>
      <arglist>(const std::string &amp;a_message)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MockProgressListener</name>
    <filename>class_mock_progress_listener.html</filename>
    <base>xms::ProgressListener</base>
    <member kind="function">
      <type>void</type>
      <name>OnProgressStatus</name>
      <anchorfile>class_mock_progress_listener.html</anchorfile>
      <anchor>ad3787ed5155e5273a31a9ae593bd5b14</anchor>
      <arglist>(int a_stackIndex, double a_fractionComplete) override</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>OnBeginOperationString</name>
      <anchorfile>class_mock_progress_listener.html</anchorfile>
      <anchor>af21e75794d759d2bf393931ace2eb870</anchor>
      <arglist>(const std::string &amp;a_operation) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>OnEndOperation</name>
      <anchorfile>class_mock_progress_listener.html</anchorfile>
      <anchor>af0af5b965bcd9ff0e5a0acae47544afe</anchor>
      <arglist>(int a_stackIndex) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>OnUpdateMessage</name>
      <anchorfile>class_mock_progress_listener.html</anchorfile>
      <anchor>a7e2a888559804e0807d7e25fd6139264</anchor>
      <arglist>(int a_stackIndex, const std::string &amp;a_message) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ProgressListener</name>
      <anchorfile>classxms_1_1_progress_listener.html</anchorfile>
      <anchor>a284b9861f146ecfe2ec6967288aca1d3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>m_messages</name>
      <anchorfile>class_mock_progress_listener.html</anchorfile>
      <anchor>ad04cb01d849d816295a88ef0c495e61c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>m_stackIndex</name>
      <anchorfile>class_mock_progress_listener.html</anchorfile>
      <anchor>a2ccfd4270e90754302836fb11af5e516</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SetListener</name>
      <anchorfile>classxms_1_1_progress_listener.html</anchorfile>
      <anchor>ad5c7ea41fa32cd6765b9a1e78c2ec246</anchor>
      <arglist>(BSHP&lt; ProgressListener &gt; a_listener)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static BSHP&lt; ProgressListener &gt;</type>
      <name>GetListener</name>
      <anchorfile>classxms_1_1_progress_listener.html</anchorfile>
      <anchor>a2b352b29be51b8fedcb13c95fdb7dce8</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ObserverIntermediateTests</name>
    <filename>class_observer_intermediate_tests.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual const CxxTest::TestGroup &amp;</type>
      <name>group</name>
      <anchorfile>class_observer_intermediate_tests.html</anchorfile>
      <anchor>aefbc6e786385d522f04d2e2f0f12d36e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testTimeRemaining</name>
      <anchorfile>class_observer_intermediate_tests.html</anchorfile>
      <anchor>a5634b85a70a491b549cfb7fbd56b2f43</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testMockObserver</name>
      <anchorfile>class_observer_intermediate_tests.html</anchorfile>
      <anchor>aaef4873118a7f6cf08c7c9e0ae8aa184</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ProgressUnitTests</name>
    <filename>class_progress_unit_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>testProgress</name>
      <anchorfile>class_progress_unit_tests.html</anchorfile>
      <anchor>a2277803a4d6b0f384760114b98332253</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>PtUnitTests</name>
    <filename>class_pt_unit_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>testIt</name>
      <anchorfile>class_pt_unit_tests.html</anchorfile>
      <anchor>a5be302172b78a117886c7efe1fa722fd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testStreams</name>
      <anchorfile>class_pt_unit_tests.html</anchorfile>
      <anchor>a4b1337a42ea2b04e6aa06afb8b57f879</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>PyObserver</name>
    <filename>class_py_observer.html</filename>
    <base>xms::PublicObserver</base>
  </compound>
  <compound kind="class">
    <name>StringUtilUnitTests</name>
    <filename>class_string_util_unit_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>testExtendedASCII</name>
      <anchorfile>class_string_util_unit_tests.html</anchorfile>
      <anchor>a74b1fa1249b28256edb3f10b7d8f2168</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testImplodeExplode</name>
      <anchorfile>class_string_util_unit_tests.html</anchorfile>
      <anchor>ab361b22a464513d5330a26eed0530987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testSuIndexOfElem</name>
      <anchorfile>class_string_util_unit_tests.html</anchorfile>
      <anchor>af54e8bc26d2b7ff1dbc26dd49558fdb5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testSplit</name>
      <anchorfile>class_string_util_unit_tests.html</anchorfile>
      <anchor>a36ef7251144f3b52187b1bc9ef91b031</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testMakeUnique</name>
      <anchorfile>class_string_util_unit_tests.html</anchorfile>
      <anchor>a733d330366309bcd655802052e71d382</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testTrim</name>
      <anchorfile>class_string_util_unit_tests.html</anchorfile>
      <anchor>a0ff4446dd4516e6fd1b2a3a1148ee349</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testReplace</name>
      <anchorfile>class_string_util_unit_tests.html</anchorfile>
      <anchor>a267005201b67c8e568be1bd8201bc37b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testCountChar</name>
      <anchorfile>class_string_util_unit_tests.html</anchorfile>
      <anchor>ac64221f59804ddb2cf57b3ec3fc4ee63</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testNumAndSciNot</name>
      <anchorfile>class_string_util_unit_tests.html</anchorfile>
      <anchor>a92bddb9b52b66ac8ad6240b7b4525d85</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testToUpper</name>
      <anchorfile>class_string_util_unit_tests.html</anchorfile>
      <anchor>a08347bd203879d86697e085df82bea92</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test_str2int</name>
      <anchorfile>class_string_util_unit_tests.html</anchorfile>
      <anchor>a093a7705670697ea101194b9bceca947</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testMisc</name>
      <anchorfile>class_string_util_unit_tests.html</anchorfile>
      <anchor>a565ab3d289a1c1e4125d47e5a5c308d2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testXmCommaNumpunct</name>
      <anchorfile>class_string_util_unit_tests.html</anchorfile>
      <anchor>a7dac5605ae17a419bb0d92d33f5351bd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testSuSimplified</name>
      <anchorfile>class_string_util_unit_tests.html</anchorfile>
      <anchor>abc41a29d09b1d8c93037b30f5e083dd6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testSuIcontains</name>
      <anchorfile>class_string_util_unit_tests.html</anchorfile>
      <anchor>ab026427acce0c652ee93cf0747b9725d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testSuVecContainsStr</name>
      <anchorfile>class_string_util_unit_tests.html</anchorfile>
      <anchor>a5dccaaeb653eb715c75fd7dd476a5d77</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test_STRstd</name>
      <anchorfile>class_string_util_unit_tests.html</anchorfile>
      <anchor>ac5d9c9fbf42bb87556251525787c6449</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>XmErrorUnitTests</name>
    <filename>class_xm_error_unit_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>test1</name>
      <anchorfile>class_xm_error_unit_tests.html</anchorfile>
      <anchor>a0b80b63b95b00204de6892c6cb3017e6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test_XM_ASSERT</name>
      <anchorfile>class_xm_error_unit_tests.html</anchorfile>
      <anchor>a120631a18381195cf7299b00abe0d0d1</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>XmLogUnitTests</name>
    <filename>class_xm_log_unit_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>testAll</name>
      <anchorfile>class_xm_log_unit_tests.html</anchorfile>
      <anchor>a92ef67747d37641518e792375178fdb7</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>python::misc::observer_pyt</name>
    <filename>namespacepython_1_1misc_1_1observer__pyt.html</filename>
    <class kind="class">python::misc::observer_pyt::MockObserver</class>
    <class kind="class">python::misc::observer_pyt::TestObserver</class>
  </compound>
  <compound kind="class">
    <name>python::misc::observer_pyt::MockObserver</name>
    <filename>classpython_1_1misc_1_1observer__pyt_1_1_mock_observer.html</filename>
  </compound>
  <compound kind="class">
    <name>python::misc::observer_pyt::TestObserver</name>
    <filename>classpython_1_1misc_1_1observer__pyt_1_1_test_observer.html</filename>
    <member kind="function">
      <type>def</type>
      <name>setUp</name>
      <anchorfile>classpython_1_1misc_1_1observer__pyt_1_1_test_observer.html</anchorfile>
      <anchor>a6dba6d1735b30b7609e49c411da5eb6e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>xmlog</name>
    <filename>namespacexmlog.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>MessageTypeEnum</name>
      <anchorfile>namespacexmlog.html</anchorfile>
      <anchor>a7f66c92bb821241cbb29fb07d7bce588</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>info</name>
      <anchorfile>namespacexmlog.html</anchorfile>
      <anchor>a7f66c92bb821241cbb29fb07d7bce588ac70f575410fcc0c690c6e140e609b82d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>warning</name>
      <anchorfile>namespacexmlog.html</anchorfile>
      <anchor>a7f66c92bb821241cbb29fb07d7bce588a6298031baaba1124b5b331212084dcb3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>error</name>
      <anchorfile>namespacexmlog.html</anchorfile>
      <anchor>a7f66c92bb821241cbb29fb07d7bce588a6c90100ca9f6986351a3a437374735c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>debug</name>
      <anchorfile>namespacexmlog.html</anchorfile>
      <anchor>a7f66c92bb821241cbb29fb07d7bce588a42797ff955c778a8a9e21bdd5580a92e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>std::basic_ostream&lt; CharT, TraitsT &gt; &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespacexmlog.html</anchorfile>
      <anchor>adf50b635bf1e1689ed6355668139e858</anchor>
      <arglist>(std::basic_ostream&lt; CharT, TraitsT &gt; &amp;strm, xmlog::MessageTypeEnum lvl)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>xms</name>
    <filename>namespacexms.html</filename>
    <class kind="class">xms::Observer</class>
    <class kind="class">xms::Progress</class>
    <class kind="class">xms::ProgressListener</class>
    <class kind="class">xms::Singleton</class>
    <class kind="class">xms::SharedSingleton</class>
    <class kind="class">xms::StTemp2DigitExponents</class>
    <class kind="class">xms::StCommaNumpunct</class>
    <class kind="class">xms::XmLog</class>
    <class kind="class">xms::ltPt3</class>
    <class kind="class">xms::ltPt3_2D</class>
    <class kind="class">xms::ltPt2</class>
    <class kind="class">xms::Pt2</class>
    <class kind="class">xms::Pt3</class>
    <class kind="class">xms::Pt4</class>
    <class kind="class">xms::PublicObserver</class>
    <class kind="class">xms::ETestMessagingState</class>
    <member kind="typedef">
      <type>unsigned long</type>
      <name>XM_DWORD</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9914eef47ba2ef59310b7792b11f9bc0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>XM_ULONG_PTR</type>
      <name>XM_DWORD_PTR</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aef89aab782c051695b1f554a93808789</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned short</type>
      <name>XM_WORD</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4d480ea25f374957ddccd969cc9df34a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned char</type>
      <name>XM_BYTE</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af746940725ac9170fe7618a41cd2e225</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>XM_DWORD</type>
      <name>XM_COLORREF</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aeacfbf0add472c121123b8206a36daf8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>boost::dynamic_bitset&lt; size_t &gt;</type>
      <name>DynBitset</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aba8c1eacfbbd2d1f45cef2fd55a35d93</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>boost::function&lt; std::string()&gt;</type>
      <name>XmLogFilenameCallback</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae3cd81470802b85051b6ef7e4c097535</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; std::pair&lt; xmlog::MessageTypeEnum, std::string &gt; &gt;</type>
      <name>MessageStack</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a854f1e57e755779b900d32077f1fb70c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ltPt3&lt; double &gt;</type>
      <name>ltPt3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6d6f9950b1bab04111e1f955550f4145</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ltPt3_2D&lt; double &gt;</type>
      <name>ltPt3d_2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9f8a84da20d91174924c5e637a49f133</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ltPt2&lt; double &gt;</type>
      <name>ltPt2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a308bf67d12ecae396921de946d43c489</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Pt2&lt; int &gt;</type>
      <name>Pt2i</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a518c7b2b0bcae0bdcc73126e85c83047</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Pt2&lt; float &gt;</type>
      <name>Pt2f</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9f994e9ae9086aa1fe47d87a8f8a10c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Pt2&lt; double &gt;</type>
      <name>Pt2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a744e494df03812a8bf92b5383bb48cef</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Pt3&lt; int &gt;</type>
      <name>Pt3i</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af2ee555d81375541d81fb08519bc7e3c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Pt3&lt; float &gt;</type>
      <name>Pt3f</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab48f0df70ce7acac4413e2062a5a97c2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Pt3&lt; double &gt;</type>
      <name>Pt3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a33ae0c78e599c46ba59bce7f2b32d7ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Pt4&lt; int &gt;</type>
      <name>Pt4i</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0950f9ab66e0ebdd36bb554f6421516d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Pt4&lt; float &gt;</type>
      <name>Pt4f</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aa8bce394e573e9cb3aee50e088a829ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Pt4&lt; double &gt;</type>
      <name>Pt4d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>afefc2ac7e0e4006c5984dcfb74a4f8b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::deque&lt; Pt2d &gt;</type>
      <name>DEQ_PT2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad17ebff442a5af50e93b027dc76fac07</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::deque&lt; Pt2d &gt;</type>
      <name>DeqPt2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab075c6283191e8574d5b982e7a059e03</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>stdext::hash_map&lt; std::string, std::string &gt;</type>
      <name>HASH_S_S</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a56e54e0912307d4de71a4d78d8d68278</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>stdext::hash_map&lt; int, std::string &gt;</type>
      <name>HASH_I_S</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>acaab4614cdb61c53069a10e3e3900992</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>stdext::hash_map&lt; std::string, std::string &gt;</type>
      <name>HashStrStr</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aed890677ebeb23e366bf88d576a1fa8d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>stdext::hash_map&lt; int, std::string &gt;</type>
      <name>HashIntStr</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a70bd6170c9e2680843e379eb968b43c5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::list&lt; Pt2d &gt;</type>
      <name>LIST_MP2</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a752b01cd2f5da0f0666c9b8d618d3e73</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::list&lt; Pt2d &gt;</type>
      <name>ListPt2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae9fd3d8a0d241b1da7cf2f6b22e13fb7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; double, double &gt;</type>
      <name>MapDblDbl</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a96319792209e6107cd0c7fb2405e838d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; double, int &gt;</type>
      <name>MapDblInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a760083c970c1c8999eba9c675e18fe0f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; double, std::string &gt;</type>
      <name>MapDblStr</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>adcebdd9d2d0a5791feee0022ed6615e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, bool &gt;</type>
      <name>MapIntBool</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8873858f58439ef2542640d460f2f2ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, double &gt;</type>
      <name>MapIntDbl</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a320d3c4b7bd375eb56ba1a48eb9531aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, float &gt;</type>
      <name>MapIntFlt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5a8fd93dc68064b65820a0673f8c470d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, float ** &gt;</type>
      <name>MapIntFlt2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a13a075958351f2bd9c53dc5e071875c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, int &gt;</type>
      <name>MapIntInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae04b2b1c55d9731d0a5cb1df2e2e45fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, SetInt &gt;</type>
      <name>MapIntSetInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aaf8f06591bf3cfa69ccdbdebb689d435</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, std::string &gt;</type>
      <name>MapIntStr</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a42e244f0cc8aaea1c3a5808c502090b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, Pt3d &gt;</type>
      <name>MapIntPt3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a96099a3e91d4511fbb214f2aee566ebe</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, VecDbl &gt;</type>
      <name>MapIntVecDbl</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>acfd1315a0883ffe944d1f6f065e11d77</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, VecFlt &gt;</type>
      <name>MapIntVecFlt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6a6a53a2f851e3ddae669175cb634332</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, VecFlt2d &gt;</type>
      <name>MapIntVecFlt2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4fc6842b97a35032224a67a3cf147449</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, VecInt &gt;</type>
      <name>MapIntVecInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af48f45bc066cf776edc51b449195b6f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, MapIntDbl &gt;</type>
      <name>MapIntMapIntDbl</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a86f52b0704e63cda25c422352c7096ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, MapIntFlt &gt;</type>
      <name>MapIntMapIntFlt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a29a10625efb925d32ccf1bb89e9a8d81</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, MapIntInt &gt;</type>
      <name>MapIntMapIntInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aa093012c3a6b357d08907f5039abcbfa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; Pt3d, int &gt;</type>
      <name>MapPt3dInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5de588db3d596532fe6b9df5703fc93d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; std::string, double &gt;</type>
      <name>MapStrDbl</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8c3c2d9bcbe0e5bc777263dc39a1b5f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; std::string, int &gt;</type>
      <name>MapStrInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3237d9d174ce16a2443db939380ce83d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; std::string, MapIntDbl &gt;</type>
      <name>MapStrMapIntDbl</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a34bedebf9a1985bdf4424fb9f2beff93</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; std::string, std::string &gt;</type>
      <name>MapStrStr</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4a10c2e6f4da3c31779497493b88e086</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; std::string, VecStr &gt;</type>
      <name>MapStrVecStr</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac3b01f9f75e31dff0c2dd37d68409b02</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::multimap&lt; bool, int &gt;</type>
      <name>MmapBoolInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad2d0318b5dbae330617f569db3213c82</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::multimap&lt; double, int &gt;</type>
      <name>MmapDblInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a96e869281d10830ca3935720cbaba8dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::multimap&lt; int, int &gt;</type>
      <name>MmapIntInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>acb4ccb3448b7899772bd48d7fff52a1c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::multimap&lt; std::string, int &gt;</type>
      <name>MmapStrInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a663bb1c6bd93293cf091ab7fdff684c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::set&lt; Pt2d &gt;</type>
      <name>SetPt2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>abe338c6aad290b9e63a796b089580a2d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::set&lt; Pt3d &gt;</type>
      <name>SetPt3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ace0c4bf93aa2fbca1de7fdba9e31c054</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::set&lt; Pt4d &gt;</type>
      <name>SetPt4d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a131d97f1b3c7a688577d2ac1d7206f1f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::set&lt; size_t &gt;</type>
      <name>SetSizet</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8701e9932125a2152d0ffc5d6b301d55</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::set&lt; int &gt;</type>
      <name>SetInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af6291e795c0018d80c22e2bd9bc2888c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::set&lt; int64_t &gt;</type>
      <name>SetInt64</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aeba38cc9ea2c11044a95c0eba06a9bb9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::set&lt; float &gt;</type>
      <name>SetFlt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>abea86738bccb0a9444cedb046c9b74a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::set&lt; double &gt;</type>
      <name>SetDbl</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab68506e4a18b8a7de878eb9181cfda56</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::set&lt; std::string &gt;</type>
      <name>SetStr</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a33394672ae51929bc113aebffe9069d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::pair&lt; int, int &gt;</type>
      <name>PAIR_I_I</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad9330a096ca1941af220275e240016d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; bool &gt;</type>
      <name>VecBool</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a050c6b4a3040009b4bf6fc7f73714c9f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; char &gt;</type>
      <name>VecChar</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>afd4eedad4cc93746d505257ad086bd53</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; unsigned char &gt;</type>
      <name>VecUchar</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a929375fccc7c71c456bc6e1ef22909b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; double &gt;</type>
      <name>VecDbl</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5de59c68ff16d81cb2a429173f3a2fa5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; float &gt;</type>
      <name>VecFlt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a386622729e9b0e733d6eaac4e0e711c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; int &gt;</type>
      <name>VecInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad81e1ef6499bc0e65df973717a1e2fbb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; unsigned int &gt;</type>
      <name>VecUint</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a90633b22271b64f73e832ef9a023c282</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; short &gt;</type>
      <name>VecShort</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0583923a141e14a792e63d480a4927d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; std::string &gt;</type>
      <name>VecStr</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aec782765108bad312607f9ddcc90eb62</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; void * &gt;</type>
      <name>VecVoid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a63374baf974e2f7d75033f9866214ea4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; std::size_t &gt;</type>
      <name>VecSizet</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a7b87d9c3ada9a6c1d3684a09247fbbeb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecFlt &gt;</type>
      <name>VecFlt2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a7f783acf77704ab019a31d867e2548ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecInt &gt;</type>
      <name>VecInt2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a91ad569308b76393ca27c1270a637d9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecDbl &gt;</type>
      <name>VecDbl2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a139b3b5faf4391ffae6815bd68d7d68d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecStr &gt;</type>
      <name>VecStr2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aa5e84be6ceaa52d7140282252bf8fe4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecSizet &gt;</type>
      <name>VecSizet2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a91de3187e7a3c1cd3e0ecfb21a1782c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecFlt2d &gt;</type>
      <name>VecFlt3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aeac46db5bf5f0ab49abef27f808d8464</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecInt2d &gt;</type>
      <name>VecInt3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aac1c2f8265a306e691d4ab1ac2300f2b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecDbl2d &gt;</type>
      <name>VecDbl3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>adb29b07af3808422651d57e2de63afef</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecStr2d &gt;</type>
      <name>VecStr3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a13ddd673c4b345fffc41cd95807d429a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecDbl3d &gt;</type>
      <name>VecDbl4d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a7b7add4774d4dfdd6233a6d5b8c3f3f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecFlt3d &gt;</type>
      <name>VecFlt4d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a54c7589307bbbfc081e02e0114c1eff5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; Pt4d &gt;</type>
      <name>VecPt4d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>abea17c4af0781cb9a16dd7970a73fbfc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; Pt3d &gt;</type>
      <name>VecPt3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0dc29604ee813731d584232b63f54922</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; Pt3f &gt;</type>
      <name>VecPt3f</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a17a077741174f8fc1e40e8513983a46b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; Pt2d &gt;</type>
      <name>VecPt2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af62f55649566e3c0cae2c9547031c5ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; Pt2f &gt;</type>
      <name>VecPt2f</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>acaa0f15a13b3ed7a9a6c6efe852f0637</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; Pt2i &gt;</type>
      <name>VecPt2i</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4981187cb84e75c3a25e19e3fe0a6f73</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecPt2d &gt;</type>
      <name>VecPt2d2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aab85a4b0741ae0758048122842ddfc49</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecPt2f &gt;</type>
      <name>VecPt2f2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac49e25a9f1734d84a0c6ad51b5aedf9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecPt3d &gt;</type>
      <name>VecPt3d2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a1b0ce86e91b176c54f0f122476873c75</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecPt3f &gt;</type>
      <name>VecPt3f2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a2256d4c8e906d3ed11857188957b2154</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecPt3d2d &gt;</type>
      <name>VecPt3d3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3baed22b50d99fef3f3bc78c99eaf26f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>PrecFlags</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a150c15c1d0a88f50f4d712f9d9be3008</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>STR_FLOAT</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a150c15c1d0a88f50f4d712f9d9be3008a48bb11800c4a7fa2d7322427b881a6c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>STR_SCIENTIFIC</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a150c15c1d0a88f50f4d712f9d9be3008a082a9602c7c50dad0fe698b5d58c8808</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>STR_USEMAXPREC</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a150c15c1d0a88f50f4d712f9d9be3008aaed962324766743f9927850945772b06</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>STR_FULLWIDTH</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a150c15c1d0a88f50f4d712f9d9be3008a0cab439cf05ec71900dadea89ec9577e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>STR_WITHCOMMAS</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a150c15c1d0a88f50f4d712f9d9be3008a6b948c99ca149c735b9f974c8269c0bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>xmresult</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a1503071e7b25b13081f9f478658a1046</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Round</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>adfc1700dbd9064558f9fc863ebf041eb</anchor>
      <arglist>(_T a)</arglist>
    </member>
    <member kind="function">
      <type>_T</type>
      <name>Miabs</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a84070d6a77796325193e66c78ca154aa</anchor>
      <arglist>(_T a)</arglist>
    </member>
    <member kind="function">
      <type>_T</type>
      <name>Mfabs</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a05c138381112b821d1b787e9a00ec7bf</anchor>
      <arglist>(_T a)</arglist>
    </member>
    <member kind="function">
      <type>_T</type>
      <name>Mmax</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a1ebfb4727e5e32fd9c5ff54bbe1eb00d</anchor>
      <arglist>(_T a, _U b)</arglist>
    </member>
    <member kind="function">
      <type>_T</type>
      <name>Mmin</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a49767d69c41924570a9ba7618a1ab347</anchor>
      <arglist>(_T a, _U b)</arglist>
    </member>
    <member kind="function">
      <type>_T</type>
      <name>Mmax3</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a704792bfcc46cdf8985064c2aa682cbf</anchor>
      <arglist>(_T a, _U b, _V c)</arglist>
    </member>
    <member kind="function">
      <type>_T</type>
      <name>Mmin3</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aff5b55ba164ee1413aa3642672016f88</anchor>
      <arglist>(_T a, _U b, _V c)</arglist>
    </member>
    <member kind="function">
      <type>_T</type>
      <name>sqr</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aa101a2a7d9f16080d4ff39ef821e36cf</anchor>
      <arglist>(const _T x)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Mdist</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a98aa9ce14bd15da1a7bf8967c9fe7859</anchor>
      <arglist>(_T x1, _U y1, _V x2, _W y2)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>MdistSq</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af8a2d48751fbb04d767cc893412654b1</anchor>
      <arglist>(_T x1, _U y1, _V x2, _W y2)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Mdist</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aadbee364d0afc6d54374e612e2c48ab4</anchor>
      <arglist>(X1 x1, Y1 y1, Z1 z1, X2 x2, Y2 y2, Z2 z2)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>MagSquared</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5fbdecf465138bd8c97d71bb82fa7681</anchor>
      <arglist>(_T const x, _T const y, _T const z=0, _T const w=0)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Mag</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>adfc065e9706d90143ae53420a9cf1b2c</anchor>
      <arglist>(_T const x, _T const y, _T const z=0, _T const w=0)</arglist>
    </member>
    <member kind="function">
      <type>_T</type>
      <name>Clamp</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a2fd4ced1304195c63c72c132a2318891</anchor>
      <arglist>(_T a_in, _T a_min, _T a_max)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EQ_EPS</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aae3e3dee54b4e049573f92c74a38f79f</anchor>
      <arglist>(_T A, _U B, _V epsilon)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>LT_EPS</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aaff8b48b5ad5f026e35bc38f1aab1ca7</anchor>
      <arglist>(_T A, _U B, _V epsilon)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GT_EPS</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a661b4e1380df8833eb664d864a0868e0</anchor>
      <arglist>(_T A, _U B, _V epsilon)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>LTEQ_EPS</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a68b550210e6ca81a802f5ba2fc88c2e7</anchor>
      <arglist>(_T A, _U B, _V epsilon)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GTEQ_EPS</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4c0dd874e2af06c9ea53bee53a0f8809</anchor>
      <arglist>(_T A, _U B, _V epsilon)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EQ_TOL</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad2b764be90f289082998491db1b52711</anchor>
      <arglist>(const _T &amp;A, const _U &amp;B, const _V &amp;tolerance)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>LT_TOL</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4cfdbe3e6a4d961c82a96926619f5a9f</anchor>
      <arglist>(_T A, _U B, _V tolerance)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GT_TOL</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab8190cb81d709d785efaa01409c342c2</anchor>
      <arglist>(_T A, _U B, _V tolerance)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>LTEQ_TOL</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6e651752f23c660cebe5561ae9e9b374</anchor>
      <arglist>(_T A, _U B, _V tol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GTEQ_TOL</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae0787a6aa8fbfb21f298cea14409af25</anchor>
      <arglist>(_T A, _U B, _V tol)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; T &gt;</type>
      <name>CopyBSHP</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3d6d80550e13f3bd87b7d6680070ba39</anchor>
      <arglist>(const BSHP&lt; T &gt; &amp;a_in)</arglist>
    </member>
    <member kind="function">
      <type>char(&amp;</type>
      <name>caArraySizeHelper</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a7872de9419f714a93ed1c4ce76d35a6c</anchor>
      <arglist>(T(&amp;array)[N]))[N]</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>VecBooleanToDynBitset</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a07a9a5ed39e6326c5725622af98f4856</anchor>
      <arglist>(const std::vector&lt; unsigned char &gt; &amp;a_from, DynBitset &amp;a_to)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DynBitsetToVecBoolean</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>afde2102c1e6c433c09ef13194a92feeb</anchor>
      <arglist>(const DynBitset &amp;a_from, std::vector&lt; unsigned char &gt; &amp;a_to)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; ProgressListener &gt; &amp;</type>
      <name>iListener</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4e7e0625acb9a639f0a22b16a7c40267</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>stCountChar</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a66dc21c168b37fd14baa201e35d24303</anchor>
      <arglist>(const std::string &amp;str, char c)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>stNumeric</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab0b7eb9e82512404cfbc9a27b6559581</anchor>
      <arglist>(const std::string &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>stScientificNotation</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ace822764b0cde4e3baf45bda5a79278e</anchor>
      <arglist>(const std::string &amp;str, bool check_numeric)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stChangeExtendedAscii</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0c7be175c9d3dfece6b1ef294c2bb7a5</anchor>
      <arglist>(std::string &amp;str, bool to_extended)</arglist>
    </member>
    <member kind="function">
      <type>VecStr</type>
      <name>stExplode</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a57dc839bc15e3dd666e5dc4f760c306a</anchor>
      <arglist>(const std::string &amp;source, const std::string &amp;a_delimiter)</arglist>
    </member>
    <member kind="function">
      <type>VecStr</type>
      <name>stSplit</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a017a40f9bede43b498c72da02bd467df</anchor>
      <arglist>(const std::string &amp;a_source, const std::string &amp;a_delimiterList, bool a_delimiterCompressOn)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>stImplode</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6a337b11d65b3a9417cba2112e74b508</anchor>
      <arglist>(const std::vector&lt; std::string &gt; &amp;source, const std::string &amp;delim)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>stIndexOfElem</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aaa0728c7493daa64d15c1cb841a6a497</anchor>
      <arglist>(const VecStr &amp;a_container, const std::string &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>stTrimCopy</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a84d62f26c1fc187d83b46b84b3cf43b9</anchor>
      <arglist>(const std::string &amp;str, const std::string &amp;delim)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>stTrimLeft</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aeb97c544ba43a601c6eda91cf7b35660</anchor>
      <arglist>(std::string &amp;str, const std::string &amp;delim)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>stTrimRight</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a24b3a75ddb15e1a3af63ace78743698e</anchor>
      <arglist>(std::string &amp;str, const std::string &amp;delim)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>stTrim</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a39d7f16b6e977ae32527ea53fe4b9787</anchor>
      <arglist>(std::string &amp;str, const std::string &amp;delim)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>stReplaceCopy</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3231cbcdc9c74f4062773a434ce911d9</anchor>
      <arglist>(const std::string &amp;str, char source, char dest)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>stReplaceCopy</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae019a64c9217040cee8621d4d3d3165d</anchor>
      <arglist>(const std::string &amp;str, const std::string &amp;source, const std::string &amp;dest)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>stReplace</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac9581f4c28c356b74396dba117269ae1</anchor>
      <arglist>(std::string &amp;str, char source, char dest)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>stReplace</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a388e8a7ed3aa5ad71577af5d80e56d92</anchor>
      <arglist>(std::string &amp;str, const std::string &amp;source, const std::string &amp;dest)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>stRemoveCopy</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>abf72758241ec1e075a523e39c3b3c344</anchor>
      <arglist>(const std::string &amp;str, char source)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>stRemove</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aafff78bb96f6fbeea2f19f109a5437e2</anchor>
      <arglist>(std::string &amp;str, char source)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>stToLowerCopy</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aa23e586099822b2abf95667edda1e5ac</anchor>
      <arglist>(const std::string &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>stToLower</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a7505715e7657aaf00882cbef93bb5207</anchor>
      <arglist>(std::string &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>stToUpperCopy</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a256855911dbcfa820f371cd2e1e51dda</anchor>
      <arglist>(const std::string &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>stToUpper</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a1a830ff5f0993e00e18f160b7688587e</anchor>
      <arglist>(std::string &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>stLeftCopy</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>abaebc05a9850a63de0a2e97cd846f003</anchor>
      <arglist>(const std::string &amp;a_source, size_t const a_length)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>stLeft</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8c8313510105ac074df3d8b2bb31a19d</anchor>
      <arglist>(std::string &amp;a_source, size_t const a_length)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>stRightCopy</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aef112f15bf17156747a46651c3091327</anchor>
      <arglist>(const std::string &amp;a_source, size_t const a_length)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>stSimplified</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a923ca5adb7e740d260c6107a30eb92e4</anchor>
      <arglist>(const std::string &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>stContains</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>afd009be52d6dc920921393aefb392a47</anchor>
      <arglist>(const std::string &amp;a_container, const std::string &amp;a_substr)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>stVectorContainsString</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5dbf6882ae8b9a61712f6804976332bd</anchor>
      <arglist>(const VecStr &amp;a_container, const std::string &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>stRight</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab67b6dca5ea3213603fddba4f20dc01d</anchor>
      <arglist>(std::string &amp;a_source, size_t const a_length)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>stEqualNoCase</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a99069b19783ed6a9afce2bcf67b90509</anchor>
      <arglist>(const std::string &amp;a, const std::string &amp;b)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>stFindNoCase</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a92aeadb401decb6f069031aa823ea71c</anchor>
      <arglist>(const std::string &amp;a, const std::string &amp;b)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>stMakeUnique</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8c105a0f5188c2ffd832849a06828d56</anchor>
      <arglist>(const std::set&lt; std::string &gt; &amp;set_str, std::string &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>stStringToInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aba35915722db9ac0e5a10fbfcdcf4d3a</anchor>
      <arglist>(const std::string &amp;s, int &amp;i, int base)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>stStringToDouble</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a13129a1a44d72d661112e936365ef4cf</anchor>
      <arglist>(const std::string &amp;s, double &amp;d)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>stPrecision</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab717e5d6ed20083c488f249bd4d98659</anchor>
      <arglist>(double value, int &amp;flags, int length)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>STRstd</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac1a247a3a486723b3ce08d4e732845f3</anchor>
      <arglist>(double a_value, int a_n, int width, int flags)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>STRstd</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a1d8fdd4c8a76a30d5cdbf056aa8e96a0</anchor>
      <arglist>(float value, int n, int width, int flags)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>STRstd</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a029b7e2c274fc5487dfc32a84ea915ea</anchor>
      <arglist>(std::string value)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>STRstd</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a309788d8d6f39ac0cb2f7691b11e8623</anchor>
      <arglist>(T a_value, int a_n=0, int width=0, int flags=0)</arglist>
    </member>
    <member kind="function">
      <type>bool &amp;</type>
      <name>xmAsserting</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a321716f8c5b486484ad8b9b88e4cb919</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>XM_FAILED_impl</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3969685e7c69e4ed2b8a0a7ab2838abe</anchor>
      <arglist>(xmresult _xmresult)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_LOG_INLINE_GLOBAL_LOGGER_INIT</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab86edb3135a35aac19595535d700947d</anchor>
      <arglist>(xms_global_log, boost::log::sources::severity_logger_mt&lt; xmlog::MessageTypeEnum &gt;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>iTest_XM_LOG_debug</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0acbea17ab71fd0680dd8c0bbfa0de80</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>iTest_XM_LOG_stackable</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a561ace2fc12a6562ca762ea42fb500f9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>iTest_XM_LOG_gui</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a196857566df5570c425f3982f09a0ce0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Pt2&lt; _T &gt;</type>
      <name>ptTruncate</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>afda18734bb330566478b7c50e405e597</anchor>
      <arglist>(Pt2&lt; _T &gt; const &amp;a_in)</arglist>
    </member>
    <member kind="function">
      <type>Pt3&lt; _T &gt;</type>
      <name>ptTruncate</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a15e2575a62d327a99473f9365ebeadf7</anchor>
      <arglist>(Pt3&lt; _T &gt; const &amp;a_in)</arglist>
    </member>
    <member kind="function">
      <type>Pt4&lt; _T &gt;</type>
      <name>ptTruncate</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab0369aa2588f1c303b03b0319190562c</anchor>
      <arglist>(Pt4&lt; _T &gt; const &amp;a_in)</arglist>
    </member>
    <member kind="function">
      <type>Pt3&lt; T &gt;</type>
      <name>operator*</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a631780f1735d5928d3613a6cba3c7f66</anchor>
      <arglist>(int a, const Pt3&lt; T &gt; &amp;pt)</arglist>
    </member>
    <member kind="function">
      <type>Pt3&lt; T &gt;</type>
      <name>operator*</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>abab9e54c65c43c4da48f3609d6a82f42</anchor>
      <arglist>(float a, const Pt3&lt; T &gt; &amp;pt)</arglist>
    </member>
    <member kind="function">
      <type>Pt3&lt; T &gt;</type>
      <name>operator*</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad616ca2ecb89f938799154b405ea66a7</anchor>
      <arglist>(double a, const Pt3&lt; T &gt; &amp;pt)</arglist>
    </member>
    <member kind="function">
      <type>_To &amp;</type>
      <name>Pt3Convert</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a659e78a80e43ed5eddb137738c8bba28</anchor>
      <arglist>(const _From &amp;a_from, _To &amp;a_to)</arglist>
    </member>
    <member kind="function">
      <type>std::basic_ostream&lt; charT, traits &gt; &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac664d3911e8b952aedb47b8aa7fcbe92</anchor>
      <arglist>(std::basic_ostream&lt; charT, traits &gt; &amp;strm, const Pt2&lt; T &gt; &amp;a_pt)</arglist>
    </member>
    <member kind="function">
      <type>std::basic_istream&lt; charT, traits &gt; &amp;</type>
      <name>operator&gt;&gt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab144710d1aa9fda03fd1443dbe58d9b5</anchor>
      <arglist>(std::basic_istream&lt; charT, traits &gt; &amp;strm, Pt2&lt; T &gt; &amp;a_pt)</arglist>
    </member>
    <member kind="function">
      <type>std::basic_ostream&lt; charT, traits &gt; &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac2e166377153c8720707026ead37f326</anchor>
      <arglist>(std::basic_ostream&lt; charT, traits &gt; &amp;strm, const Pt3&lt; T &gt; &amp;a_pt)</arglist>
    </member>
    <member kind="function">
      <type>std::basic_istream&lt; charT, traits &gt; &amp;</type>
      <name>operator&gt;&gt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5bd13d3b7d8191820833e7cba519f7d0</anchor>
      <arglist>(std::basic_istream&lt; charT, traits &gt; &amp;strm, Pt3&lt; T &gt; &amp;a_pt)</arglist>
    </member>
    <member kind="function">
      <type>std::basic_ostream&lt; charT, traits &gt; &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a371ec7fc6076bc607aac9ad86cabd3e6</anchor>
      <arglist>(std::basic_ostream&lt; charT, traits &gt; &amp;strm, const Pt4&lt; T &gt; &amp;a_pt)</arglist>
    </member>
    <member kind="function">
      <type>std::basic_istream&lt; charT, traits &gt; &amp;</type>
      <name>operator&gt;&gt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a76c9fa0b148a3a01b927943faad3b7b9</anchor>
      <arglist>(std::basic_istream&lt; charT, traits &gt; &amp;strm, Pt4&lt; T &gt; &amp;a_pt)</arglist>
    </member>
    <member kind="function">
      <type>Pt3d</type>
      <name>Pt3dFromPyIter</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af8bd6c40daeb861c5adaf92f11abdf56</anchor>
      <arglist>(const py::tuple &amp;pt)</arglist>
    </member>
    <member kind="function">
      <type>py::tuple</type>
      <name>PyIterFromPt3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8d24b1f36c9883e275f3d151f757bcf8</anchor>
      <arglist>(const Pt3d &amp;pt)</arglist>
    </member>
    <member kind="function">
      <type>boost::shared_ptr&lt; VecPt3d &gt;</type>
      <name>VecPt3dFromPyIter</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a43267849a6908be20246a8237928dcbf</anchor>
      <arglist>(const py::iterable &amp;pts)</arglist>
    </member>
    <member kind="function">
      <type>py::iterable</type>
      <name>PyIterFromVecPt3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8e892242a41a91506ce59befc5ca2f84</anchor>
      <arglist>(const VecPt3d &amp;pts)</arglist>
    </member>
    <member kind="function">
      <type>boost::shared_ptr&lt; VecPt3d2d &gt;</type>
      <name>VecPt3d2dFromPyIter</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8341d3f2b243f05d88a293f90a0febbb</anchor>
      <arglist>(const py::iterable &amp;pts)</arglist>
    </member>
    <member kind="function">
      <type>py::iterable</type>
      <name>PyIterFromVecPt3d2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3e5f96042bb96b842510d6199ce14b25</anchor>
      <arglist>(const VecPt3d2d &amp;pts)</arglist>
    </member>
    <member kind="function">
      <type>boost::shared_ptr&lt; VecInt2d &gt;</type>
      <name>VecInt2dFromPyIter</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aa4c0bf973be9e1f13c1f793eff468b37</anchor>
      <arglist>(const py::iterable &amp;int2d)</arglist>
    </member>
    <member kind="function">
      <type>py::iterable</type>
      <name>PyIterFromVecInt2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0a1a01df38749fc3086ebfc93d8598da</anchor>
      <arglist>(const VecInt2d &amp;int2d)</arglist>
    </member>
    <member kind="function">
      <type>boost::shared_ptr&lt; VecInt &gt;</type>
      <name>VecIntFromPyIter</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3685fbd2c82bfe5ae4ec3e1e978d8d92</anchor>
      <arglist>(const py::iterable &amp;ints)</arglist>
    </member>
    <member kind="function">
      <type>py::iterable</type>
      <name>PyIterFromVecInt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a916a7b311cc18c5c1c9720be157b3d0b</anchor>
      <arglist>(const VecInt &amp;ints, bool numpy)</arglist>
    </member>
    <member kind="function">
      <type>boost::shared_ptr&lt; VecDbl &gt;</type>
      <name>VecDblFromPyIter</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab5fd3653a6331570a61ff881917641ca</anchor>
      <arglist>(const py::iterable &amp;dbls)</arglist>
    </member>
    <member kind="function">
      <type>py::iterable</type>
      <name>PyIterFromVecDbl</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4f49d28bec256c7554c7546ff58df20a</anchor>
      <arglist>(const VecDbl &amp;dbls, bool numpy)</arglist>
    </member>
    <member kind="function">
      <type>boost::shared_ptr&lt; VecFlt &gt;</type>
      <name>VecFltFromPyIter</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8bddf97e8dc7cb2d2bcd1df5e477efb1</anchor>
      <arglist>(const py::iterable &amp;flts)</arglist>
    </member>
    <member kind="function">
      <type>py::iterable</type>
      <name>PyIterFromVecFlt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a7b285c38273bed1a3d6f3af5d3cbf357</anchor>
      <arglist>(const VecFlt &amp;flts, bool numpy)</arglist>
    </member>
    <member kind="function">
      <type>DynBitset</type>
      <name>DynamicBitsetFromPyIter</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a49bb2e3cc528e336292b521275482042</anchor>
      <arglist>(const py::iterable &amp;bitset)</arglist>
    </member>
    <member kind="function">
      <type>py::iterable</type>
      <name>PyIterFromDynamicBitset</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a598b964e4faeea76790729781310ef21</anchor>
      <arglist>(const DynBitset &amp;bitset, bool numpy)</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; int, int &gt;</type>
      <name>IntPairFromPyIter</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad1c4eab1d9f098f293e8205a2c372788</anchor>
      <arglist>(const py::iterable &amp;intpair)</arglist>
    </member>
    <member kind="function">
      <type>py::iterable</type>
      <name>PyIterFromIntPair</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>abb18038767a6eef784fe157b79ab5bd3</anchor>
      <arglist>(const std::pair&lt; int, int &gt; &amp;intpair)</arglist>
    </member>
    <member kind="function">
      <type>boost::shared_ptr&lt; std::vector&lt; std::pair&lt; int, int &gt; &gt; &gt;</type>
      <name>VecIntPairFromPyIter</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>afcdebdd67720da722a796de78c531f2e</anchor>
      <arglist>(const py::iterable &amp;intpairs)</arglist>
    </member>
    <member kind="function">
      <type>py::iterable</type>
      <name>PyIterFromVecIntPair</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a90078769bd51c076d22a3911983acaf6</anchor>
      <arglist>(const std::vector&lt; std::pair&lt; int, int &gt;&gt; &amp;intpairs)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a82b65663cc847bc0db8ac4c0930406fb</anchor>
      <arglist>(std::ostream &amp;a_output, const std::map&lt; _T, _U &gt; &amp;a_value)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a89dc698eb82bff44b24c6a00427aeedb</anchor>
      <arglist>(std::ostream &amp;a_output, const std::multimap&lt; _T, _U &gt; &amp;a_value)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a02ae6e1c76aef482f18d88a992ba0ad9</anchor>
      <arglist>(std::ostream &amp;a_output, const std::set&lt; _T &gt; &amp;a_value)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac1d111686a755d63ff7ff55c80450e9e</anchor>
      <arglist>(std::ostream &amp;a_output, const std::pair&lt; _T, _U &gt; &amp;a_value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>VecToStream</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9be33abf1221de1679a4ff237b549efb</anchor>
      <arglist>(std::stringstream &amp;a_ss, const T &amp;a_v, std::string a_label)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad55f289cf34d6e2f8baad6daf5b566f4</anchor>
      <arglist>(std::ostream &amp;a_output, const std::vector&lt; _T &gt; &amp;a_value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stShrinkCapacity</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>adb9ba9ba787e4ecd0017e0b2b149c564</anchor>
      <arglist>(std::vector&lt; T &gt; &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>ttDefaultXmsngTestPath</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aea25a4299c927c1733790a4dc3bc0882</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>ttGetXmsngTestPath</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>acddaa287c080f4199d840c9ca3e29f23</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ttByPassMessages</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9a6679c474ce3bc806395023736dcfe6</anchor>
      <arglist>(int a_defaultChoice)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ttSkippingMessages</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac8e299c3d55effb9358f87e945692da4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ttByPassDefault</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad062784654592a88d525970efcc8d914</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ttClearSkippingMessages</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aca82daee4102af38576458952c71be04</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ETestMessagingState &amp;</type>
      <name>ttTestMessagingState</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a99d430c07eede7029ba975abe116b5e9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ttCheckXmLogForEachTest</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a89a1187517e055debbd1f536e50f0a03</anchor>
      <arglist>(bool a_setting)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ttCheckXmLogForEachTest</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0af2260e97dd0a9508b272401bc13333</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ttAssertStackedErrors</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac619b9bd692506c31fba6febdd34136e</anchor>
      <arglist>(const char *a_file, int a_line, const std::string &amp;a_expected)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ttGetTestFilePaths</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a21c6cbf8cb7289e3ac5adf2c02f3db62</anchor>
      <arglist>(const std::string &amp;a_path, const std::string &amp;a_fileBase, const std::string &amp;a_extension, std::string &amp;a_baseFilePath, std::string &amp;a_outFilePath)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ttTextFilesEqual</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a326ac713f6a09e5de3b4afdb3a8f0bd5</anchor>
      <arglist>(const std::string &amp;a_file1, const std::string &amp;a_file2, std::string &amp;a_message)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ttTextFilesEqual</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af756be86cffac9304409c60bba5dbafd</anchor>
      <arglist>(const std::string &amp;a_srcFile, unsigned a_line, const std::string &amp;a_file1, const std::string &amp;a_file2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ttStreamsEqual</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab4a12bdfe2030df3dafdd066679656d1</anchor>
      <arglist>(const std::string &amp;a_src, unsigned int a_line, std::istream &amp;a_strm1, std::istream &amp;a_strm2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ttEqualWithinTolerance</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab2413ef9370a53971fba0302d9899c84</anchor>
      <arglist>(_T A, _U B, _V tolerance)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ttAssertDeltaVec</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a60ce526c07fa6f1fb54bf3713ae93c9a</anchor>
      <arglist>(const char *f, unsigned l, const std::vector&lt; T &gt; &amp;a, const std::vector&lt; T &gt; &amp;b, U delta)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ttAssertDeltaVec2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae98e466f8d6113a5361c16aa586427e6</anchor>
      <arglist>(const char *f, unsigned l, const std::vector&lt; std::vector&lt; T &gt; &gt; &amp;a, const std::vector&lt; std::vector&lt; T &gt; &gt; &amp;b, U delta)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ttAssertEqualsAVec</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aeb9eb5d8ce05366856464f6258e84f85</anchor>
      <arglist>(const char *a_file, int a_line, const T *a_expected, size_t a_expectedLength, const std::vector&lt; T &gt; &amp;a_actual)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ttAssertEqualsVec2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4dbfdd1e82e9a97582b148fbeba175e4</anchor>
      <arglist>(const char *f, unsigned l, const std::vector&lt; std::vector&lt; T &gt; &gt; &amp;a, const std::vector&lt; std::vector&lt; T &gt; &gt; &amp;b)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>ST_WHITESPACE</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>adacac03ecb8d5f770a21dfe70ec3dc9f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>XM_INT_HIGHEST</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a01350319705aa8fd575e571f7dc78b39</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>XM_INT_LOWEST</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a513f1bc13007d6834be52c6867b0ddc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const unsigned int</type>
      <name>XM_UINT_HIGHEST</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3819f0281d41e53e2dd323438083bc28</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const unsigned int</type>
      <name>XM_UINT_LOWEST</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8cca2290d55e78682257cb695f78bbbe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const double</type>
      <name>XM_DBL_HIGHEST</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a2405d59c64287fc04dd46a911a4f16c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const double</type>
      <name>XM_DBL_LOWEST</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a96ffa8332bb58934b5dd1927c1f5d900</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const double</type>
      <name>XM_DBL_NEAREST_ZERO</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8526fadd03c75b447ea997bfc835c213</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const float</type>
      <name>XM_FLT_HIGHEST</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>afc9f74847c61fef850b01c89862de16b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const float</type>
      <name>XM_FLT_LOWEST</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a271eb6a5b02e4cb04e7595d9d932fa4b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const float</type>
      <name>XM_FLT_NEAREST_ZERO</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a898ed1927f8720f5ff8fdc614d2206bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>XM0</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>acdef92522c0ad17d614cd15b6aa3bb38</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>XM1</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4c3305728b07d971cd598e0da2b6c91f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static XmLogFilenameCallback</type>
      <name>fg_logFilenameCallback</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aff8502089eb5f522e683cb52ea0a93ae</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::Observer</name>
    <filename>classxms_1_1_observer.html</filename>
    <class kind="class">xms::Observer::impl</class>
    <member kind="function" protection="private" virtualness="pure">
      <type>virtual void</type>
      <name>OnProgressStatus</name>
      <anchorfile>classxms_1_1_observer.html</anchorfile>
      <anchor>a3feec1a66db2c85d83d0de25dc12b3ea</anchor>
      <arglist>(double a_percentComplete)=0</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual void</type>
      <name>OnBeginOperationString</name>
      <anchorfile>classxms_1_1_observer.html</anchorfile>
      <anchor>ad3690b0ea8f9d136113a6b1a5ca3306b</anchor>
      <arglist>(const std::string &amp;a_operation)</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual void</type>
      <name>OnEndOperation</name>
      <anchorfile>classxms_1_1_observer.html</anchorfile>
      <anchor>a50c33f8ac41895e228157fa0d4a04588</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual void</type>
      <name>OnUpdateMessage</name>
      <anchorfile>classxms_1_1_observer.html</anchorfile>
      <anchor>afe3235bd5b4774946d4af1d1b3e60662</anchor>
      <arglist>(const std::string &amp;a_message)</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual void</type>
      <name>TimeRemainingInSeconds</name>
      <anchorfile>classxms_1_1_observer.html</anchorfile>
      <anchor>abe6664e2f7ba8c87353e09e477644c24</anchor>
      <arglist>(double a_remainingSeconds)</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual void</type>
      <name>TimeElapsedInSeconds</name>
      <anchorfile>classxms_1_1_observer.html</anchorfile>
      <anchor>a98b0e23e739cfbe97718638ed8255a73</anchor>
      <arglist>(double a_elapsedSeconds)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>friend</type>
      <name>ObserverT</name>
      <anchorfile>classxms_1_1_observer.html</anchorfile>
      <anchor>a9014ba5c372ca8fd9b02170ce3636408</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>BSHP&lt; impl &gt;</type>
      <name>m_p</name>
      <anchorfile>classxms_1_1_observer.html</anchorfile>
      <anchor>a9f5c846c1d73b1306bdfd23ef06190ac</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::Observer::impl</name>
    <filename>classxms_1_1_observer_1_1impl.html</filename>
    <member kind="function">
      <type>void</type>
      <name>BeginOperationString</name>
      <anchorfile>classxms_1_1_observer_1_1impl.html</anchorfile>
      <anchor>a9117ce56380817da4d907c30ff229e9c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EndOperation</name>
      <anchorfile>classxms_1_1_observer_1_1impl.html</anchorfile>
      <anchor>a149ecbc4f1ee7fbd718da8f9b88c5fd2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>ElapsedTimeInSeconds</name>
      <anchorfile>classxms_1_1_observer_1_1impl.html</anchorfile>
      <anchor>a771e88ca3833f7216df22bb69ba996bf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>EstimatedTimeRemainingInSec</name>
      <anchorfile>classxms_1_1_observer_1_1impl.html</anchorfile>
      <anchor>a4eaed90dc0e25cf1119fc449aea1fcf6</anchor>
      <arglist>(double a_percentComplete, double a_elapsedTime)</arglist>
    </member>
    <member kind="variable">
      <type>boost::timer::cpu_timer</type>
      <name>m_timer</name>
      <anchorfile>classxms_1_1_observer_1_1impl.html</anchorfile>
      <anchor>a9d51e5ce2ef2a14b65b155d33cf892d1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>m_percentComplete</name>
      <anchorfile>classxms_1_1_observer_1_1impl.html</anchorfile>
      <anchor>ad1716972789e4a3599f18bf96cc464ea</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::Progress</name>
    <filename>classxms_1_1_progress.html</filename>
    <member kind="function">
      <type></type>
      <name>Progress</name>
      <anchorfile>classxms_1_1_progress.html</anchorfile>
      <anchor>a62ad7fd24eecd4b556a21c8923f41b81</anchor>
      <arglist>(const std::string &amp;a_message)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Progress</name>
      <anchorfile>classxms_1_1_progress.html</anchorfile>
      <anchor>a093986f04a87dda5503b097ade380029</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>UpdateMessage</name>
      <anchorfile>classxms_1_1_progress.html</anchorfile>
      <anchor>a72d02beac23718b96d32891ed9fa7de9</anchor>
      <arglist>(const std::string &amp;a_message)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetItemCount</name>
      <anchorfile>classxms_1_1_progress.html</anchorfile>
      <anchor>a25ef1eea412ba4819f1250989540d154</anchor>
      <arglist>(long long a_count)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>CurrentItem</name>
      <anchorfile>classxms_1_1_progress.html</anchorfile>
      <anchor>adec755bc0bd7e4d86a9b4ce62f520241</anchor>
      <arglist>(long long a_item)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ProgressStatus</name>
      <anchorfile>classxms_1_1_progress.html</anchorfile>
      <anchor>ad9b48819d490b81c76a3ac0b2f8e8c3d</anchor>
      <arglist>(double a_percentComplete)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>m_stackIndex</name>
      <anchorfile>classxms_1_1_progress.html</anchorfile>
      <anchor>aca3ad3fb5dc1e55422459c6bc40b7474</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>long long</type>
      <name>m_itemCount</name>
      <anchorfile>classxms_1_1_progress.html</anchorfile>
      <anchor>ad0df175c22563c4a2d4de689effc1234</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::ProgressListener</name>
    <filename>classxms_1_1_progress_listener.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>OnProgressStatus</name>
      <anchorfile>classxms_1_1_progress_listener.html</anchorfile>
      <anchor>a4610718c85f6e6eaafb870c1f5f0edf7</anchor>
      <arglist>(int a_stackIndex, double a_fractionComplete)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>OnBeginOperationString</name>
      <anchorfile>classxms_1_1_progress_listener.html</anchorfile>
      <anchor>ac9739b5ba8d008ba4fa5b5765963960d</anchor>
      <arglist>(const std::string &amp;a_operation)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>OnEndOperation</name>
      <anchorfile>classxms_1_1_progress_listener.html</anchorfile>
      <anchor>a8ff99b96440a4e2472091eafa9fabdcc</anchor>
      <arglist>(int a_stackIndex)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>OnUpdateMessage</name>
      <anchorfile>classxms_1_1_progress_listener.html</anchorfile>
      <anchor>a1588a9e476d49ce4f0d8937781e130dd</anchor>
      <arglist>(int a_stackIndex, const std::string &amp;a_message)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::Singleton</name>
    <filename>classxms_1_1_singleton.html</filename>
    <templarg>T</templarg>
    <member kind="function" static="yes">
      <type>static T &amp;</type>
      <name>Instance</name>
      <anchorfile>classxms_1_1_singleton.html</anchorfile>
      <anchor>a9a8a1b054d5e8cea413f16a93afd480e</anchor>
      <arglist>(bool a_delete=false, T *a_new=NULL)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Delete</name>
      <anchorfile>classxms_1_1_singleton.html</anchorfile>
      <anchor>a626d4977e56e0f37c7d369834f4b235d</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::SharedSingleton</name>
    <filename>classxms_1_1_shared_singleton.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>boost::shared_ptr&lt; T &gt;</type>
      <name>Ptr</name>
      <anchorfile>classxms_1_1_shared_singleton.html</anchorfile>
      <anchor>a4aa3991d5986246d9e6d3ce16c50684d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Ptr</type>
      <name>Instance</name>
      <anchorfile>classxms_1_1_shared_singleton.html</anchorfile>
      <anchor>a1276acc05cbe856a51c4b640ffdd7445</anchor>
      <arglist>(Ptr a_new=Ptr(), bool a_delete=false)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Delete</name>
      <anchorfile>classxms_1_1_shared_singleton.html</anchorfile>
      <anchor>a76f7a809ade5852f0b238b22149c3a6e</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::StTemp2DigitExponents</name>
    <filename>classxms_1_1_st_temp2_digit_exponents.html</filename>
    <member kind="function">
      <type></type>
      <name>StTemp2DigitExponents</name>
      <anchorfile>classxms_1_1_st_temp2_digit_exponents.html</anchorfile>
      <anchor>a02180bdc964b3c70e05b723f1cb75894</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~StTemp2DigitExponents</name>
      <anchorfile>classxms_1_1_st_temp2_digit_exponents.html</anchorfile>
      <anchor>a6c3f0dc95e653a725b26cd5557497403</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>m_oldOutputFormat</name>
      <anchorfile>classxms_1_1_st_temp2_digit_exponents.html</anchorfile>
      <anchor>ae38d95e4e658a0a1566100fc45ba0fab</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::StCommaNumpunct</name>
    <filename>classxms_1_1_st_comma_numpunct.html</filename>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual char</type>
      <name>do_thousands_sep</name>
      <anchorfile>classxms_1_1_st_comma_numpunct.html</anchorfile>
      <anchor>a94e9b55f55470d2bb10f1451bff1d172</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual std::string</type>
      <name>do_grouping</name>
      <anchorfile>classxms_1_1_st_comma_numpunct.html</anchorfile>
      <anchor>aa2069686f9a15d91b346c3988be3a954</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::XmLog</name>
    <filename>classxms_1_1_xm_log.html</filename>
    <base>Singleton&lt; XmLog &gt;</base>
    <class kind="class">xms::XmLog::Impl</class>
    <member kind="function">
      <type></type>
      <name>~XmLog</name>
      <anchorfile>classxms_1_1_xm_log.html</anchorfile>
      <anchor>acc5f8eee341aeac5b06dba422619e5d6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Log</name>
      <anchorfile>classxms_1_1_xm_log.html</anchorfile>
      <anchor>a82db042ede308de7f85b0b55b8eb3587</anchor>
      <arglist>(const char *const a_file, int a_line, xmlog::MessageTypeEnum a_level, std::string a_message)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ErrCount</name>
      <anchorfile>classxms_1_1_xm_log.html</anchorfile>
      <anchor>a20ed692af6d8c0100c02f314c6395379</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MessageStack</type>
      <name>GetAndClearStack</name>
      <anchorfile>classxms_1_1_xm_log.html</anchorfile>
      <anchor>a931d33575128f427516bd258dd9642bd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>GetAndClearStackStr</name>
      <anchorfile>classxms_1_1_xm_log.html</anchorfile>
      <anchor>a6a0e58e950e973b880fdfd566062a38b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static XmLogFilenameCallback &amp;</type>
      <name>LogFilenameCallback</name>
      <anchorfile>classxms_1_1_xm_log.html</anchorfile>
      <anchor>ab3d175834a2ed9bff301cbf304f89f47</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::string</type>
      <name>LogFilename</name>
      <anchorfile>classxms_1_1_xm_log.html</anchorfile>
      <anchor>a8a9ac073794a7d8919c088de774811d5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static XmLog &amp;</type>
      <name>Instance</name>
      <anchorfile>classxms_1_1_singleton.html</anchorfile>
      <anchor>a9a8a1b054d5e8cea413f16a93afd480e</anchor>
      <arglist>(bool a_delete=false, XmLog *a_new=NULL)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Delete</name>
      <anchorfile>classxms_1_1_singleton.html</anchorfile>
      <anchor>a626d4977e56e0f37c7d369834f4b235d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>XmLog</name>
      <anchorfile>classxms_1_1_xm_log.html</anchorfile>
      <anchor>aa755e43cb07d364b0bce3b265569985b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>friend</type>
      <name>Singleton&lt; XmLog &gt;</name>
      <anchorfile>classxms_1_1_xm_log.html</anchorfile>
      <anchor>a7fb5edb11e589948eb870d1b327fa401</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>boost::scoped_ptr&lt; Impl &gt;</type>
      <name>m</name>
      <anchorfile>classxms_1_1_xm_log.html</anchorfile>
      <anchor>abed3e6f252bd9d475e9c14c724f52ff3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::XmLog::Impl</name>
    <filename>structxms_1_1_xm_log_1_1_impl.html</filename>
    <member kind="function">
      <type>void</type>
      <name>StackedErrToStream</name>
      <anchorfile>structxms_1_1_xm_log_1_1_impl.html</anchorfile>
      <anchor>aa02f112955c88daaff87726286897b9d</anchor>
      <arglist>(std::ostream &amp;a_os)</arglist>
    </member>
    <member kind="variable">
      <type>MessageStack</type>
      <name>m_stackedMessages</name>
      <anchorfile>structxms_1_1_xm_log_1_1_impl.html</anchorfile>
      <anchor>afac679dd307a287bc958e5716947d079</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>m_firstRun</name>
      <anchorfile>structxms_1_1_xm_log_1_1_impl.html</anchorfile>
      <anchor>a126ad2f69767f72cc2a59a67f0f5692e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::ltPt3</name>
    <filename>classxms_1_1lt_pt3.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>ltPt3</name>
      <anchorfile>classxms_1_1lt_pt3.html</anchorfile>
      <anchor>aca81f06cd30da9488787bb39f511d3fa</anchor>
      <arglist>(T a_xytol, T a_ztol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>classxms_1_1lt_pt3.html</anchorfile>
      <anchor>a1eba301c4a5f803c1e6350c3565f4a19</anchor>
      <arglist>(const Pt3&lt; T &gt; lhs, const Pt3&lt; T &gt; rhs) const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>T</type>
      <name>m_xytol</name>
      <anchorfile>classxms_1_1lt_pt3.html</anchorfile>
      <anchor>ac101d820aa054735630e8fc327484a58</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>T</type>
      <name>m_ztol</name>
      <anchorfile>classxms_1_1lt_pt3.html</anchorfile>
      <anchor>a5aed8eea503f31e7bad8c18eea13c56e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::ltPt3_2D</name>
    <filename>classxms_1_1lt_pt3__2_d.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>ltPt3_2D</name>
      <anchorfile>classxms_1_1lt_pt3__2_d.html</anchorfile>
      <anchor>ad896dfb33f879bd2bd9bd55938158c31</anchor>
      <arglist>(T a_xytol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>classxms_1_1lt_pt3__2_d.html</anchorfile>
      <anchor>a5e6b26187f3aee6cabf0f866ec772f09</anchor>
      <arglist>(const Pt3&lt; T &gt; a_lhs, const Pt3&lt; T &gt; a_rhs) const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>m_xytol</name>
      <anchorfile>classxms_1_1lt_pt3__2_d.html</anchorfile>
      <anchor>abd2de2022ca57ae2ad2ab4e515861b46</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::ltPt2</name>
    <filename>classxms_1_1lt_pt2.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>ltPt2</name>
      <anchorfile>classxms_1_1lt_pt2.html</anchorfile>
      <anchor>a6cff9142751132b8a9ed0b5f97be1274</anchor>
      <arglist>(T a_xytol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>classxms_1_1lt_pt2.html</anchorfile>
      <anchor>a6fd91856dcce5ba7ec16f4336a4248d0</anchor>
      <arglist>(const Pt2&lt; T &gt; a_lhs, const Pt2&lt; T &gt; a_rhs) const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>m_xytol</name>
      <anchorfile>classxms_1_1lt_pt2.html</anchorfile>
      <anchor>accb794e7b6ade2ba38694aaeaccaca4e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::Pt2</name>
    <filename>classxms_1_1_pt2.html</filename>
    <templarg>T</templarg>
    <member kind="function">
      <type></type>
      <name>Pt2</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>aca2079b57278ac716478ee7bc25b5f82</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Pt2</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a27beaba5c29f332ba23f0400eafba3d2</anchor>
      <arglist>(T a_x, T a_y)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Pt2</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a17a33d60873110a52c8f2b0030e7e285</anchor>
      <arglist>(const T &amp;a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Pt2</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a11fce60457b5d1dff47c05c03b16e348</anchor>
      <arglist>(const Pt2 &amp;a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Pt2</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a9b799589ef1644742e7e0be44a1a1776</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Pt2</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>ae636b9ab408344cee34115c9de5490e2</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Pt2</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a89094d06196228c3f360b35690e9efcc</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Pt2</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a07974c1bfe87d83350b897fa8ad98e54</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Pt2 &amp;</type>
      <name>operator=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a72cf59bba9893abe5768054ac83c06c7</anchor>
      <arglist>(const U &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>const Pt2 &amp;</type>
      <name>operator=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>abf48271961d8949bacc89c898308d0e4</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>const Pt2 &amp;</type>
      <name>operator=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>abb3f024ec00ee47c4fd0df535d0b4486</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>const Pt2 &amp;</type>
      <name>operator=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>ab6f98a7461809abbc9888dcf2a1e5019</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a8f60a70725e762c45c3ce85a8cc6ec1a</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a6f8ec24dfec3fea1ace8287015c497c5</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>abd597787f11e96f220ce0b2e397d70a5</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a674399fcba5a2925ddc0e4aa2bcd801b</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>ac0a992ffd6b2317fa49007f9baaf8b0b</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a15bba41d9b0e398a9e67da06a1a43636</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a3d17543483849f62c9665162ec5fc69a</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a9e5fa644390b4f1d5180a68d6e826900</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a46d3973d2ac0e3d513de5753d3abd65b</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>ac481077f205bc307a6eb97e78738f7bc</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>aaac361a4b0b2bf0c654273366dc13254</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a4e5c8e6cbeb8285e28f7a6db51628915</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a1262d431df9e8cbb82302092c6a09d76</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>af15c35fce3725e48f8d84166cddba2e0</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>aee93850d47e844098c6f62d42e6b8836</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a5da16ed466786df211c9b23a8360843d</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>ad623eeb7bf55267b1e5944f9dcafa507</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a9dd1e8f08f4832905437006a1cd4e3e7</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a43f9a400843d14652196b49befd81f70</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a68c88bc086888d152fc2b86e4b7f090a</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a8f47d88d5ee40025fd881100d20f10f4</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>ab0ef9c66a9f6bbda3f460267b1902e46</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>ae9490e339cb9712b7cfd57853f80f040</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a295cf32462284a821ff53e5e9923600b</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt2</type>
      <name>operator+</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>acfe7164de8916d59c5f0b89d38d46422</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt2</type>
      <name>operator+</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a40049c791d2a5b8b95f611186bf06a70</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt2</type>
      <name>operator+</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>ab24800b80d0dde8ad752aab89d8270a5</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt2</type>
      <name>operator+</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a68cc24b2f9aa6b63a817bd474a43d60c</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt2</type>
      <name>operator-</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>ae006e584c2964c813ec21ad08392ec61</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt2</type>
      <name>operator-</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>ab7eafea529fdc8107a3b88a6c00cc903</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt2</type>
      <name>operator-</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>abe3505d7b5b51926541eed61e370c7a2</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt2</type>
      <name>operator-</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>aafa44c8cabae5cacdb389b8fc7129111</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt2</type>
      <name>operator-</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a10d6be0a049c1c53025c306ae93997fc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Pt2</type>
      <name>operator*</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>aa1d3621ef9cb3188efee093f76ea1c93</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt2</type>
      <name>operator*</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a463081f2102af08f15448ac9aa765276</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt2</type>
      <name>operator*</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>acf2fe257373008f95cf5f8ac9e96f75c</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt2</type>
      <name>operator*</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a902cedf6290a8d28dcb9064ec19167a6</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt2</type>
      <name>operator/</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a3bcfcc718da72cae4784b466481a8b63</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt2</type>
      <name>operator/</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a2872ad3cbe720fb99cae587925477134</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt2</type>
      <name>operator/</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>acca1b8ae32766d3d77043d2508e68732</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt2</type>
      <name>operator/</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>acd1124343f620a175153e3bad645a0d8</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator+=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a3663ea73221662ae2ec4d72bd653e7a6</anchor>
      <arglist>(const U &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator+=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a0a32245fbb4d169b3a8032c874071268</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator+=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a009da91dfefcb5532ae90932ee2ae782</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator+=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a6314015b8954a4f86469913d57152610</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator-=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a67cfe709e918acae31d7e5a61cfdc5de</anchor>
      <arglist>(const U &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator-=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>aeb0bfaf75cf4570d714ade672be874eb</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator-=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>aca0a17a770983f5f4126c127aa03e159</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator-=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a7b606c3926258025052421a80db9860a</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator*=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>af1773455d2c90624b06e1f47c731a030</anchor>
      <arglist>(const U &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator*=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>af8c7985edc697b0e7890adbf70924bef</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator*=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a06ae430a98efb3b97f207b2f5dbec950</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator*=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a73a6a11d941bcc4b2badac53a83e4b04</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator/=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>aa156af3a76788d05057f78829863d910</anchor>
      <arglist>(const U &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator/=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a9c2e66262476021361775d5b65c3efb8</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator/=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a1d5dd7dc7d7e6ab359b76804d78909b9</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator/=</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>ad9d18205279b7a075e31b09837103128</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Set</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a52398509618536841a21796b4bbdc56a</anchor>
      <arglist>(T a_x, T a_y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Set</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a4902b45702f60adf4cab0107c785cefe</anchor>
      <arglist>(T a)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>operator[]</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a2c2f2c2c1794a94cfe3198e23cfb02b0</anchor>
      <arglist>(unsigned int a) const </arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>operator[]</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a42cc7deca0c9a62ecdda4adbbe262f4b</anchor>
      <arglist>(unsigned int a)</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>at</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a63496779ca70056e0d9e4820f7b5d57b</anchor>
      <arglist>(unsigned int a) const </arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>at</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a3fdc540f671924719dbce3bee0f15345</anchor>
      <arglist>(unsigned int a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>serialize</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a3700d1eb8a2341b5e1111697afc041f2</anchor>
      <arglist>(Archive &amp;archive, const unsigned int version)</arglist>
    </member>
    <member kind="variable">
      <type>T</type>
      <name>x</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>ad745ecd6452f58f494bb7272f15ba094</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>T</type>
      <name>y</name>
      <anchorfile>classxms_1_1_pt2.html</anchorfile>
      <anchor>a18572826ae6b934a324b196f0b58de88</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::Pt3</name>
    <filename>classxms_1_1_pt3.html</filename>
    <templarg>T</templarg>
    <member kind="typedef">
      <type>T</type>
      <name>value_type</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>af2484d57712d9ac194506cec5538b241</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Pt3</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a836504d6edb688fd9e6fc3e9098bb3ec</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Pt3</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a360bc1f71c5db8f7f90287c98c20fe5c</anchor>
      <arglist>(T a_x, T a_y, T a_z)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Pt3</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a52b9be5b7b1e50d37342a3a106afddc1</anchor>
      <arglist>(T a_x, T a_y)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Pt3</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>ac58383cb3f1ca419caec71a350f9099e</anchor>
      <arglist>(T a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Pt3</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>aea34622f83f1e84d5eeb5e1c6bae0b0a</anchor>
      <arglist>(const Pt3 &amp;a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Pt3</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a0d8fb86b66f94b8576c41c148718c759</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Pt3</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a44d0496a66d72e00b27bfc2e1943be4d</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Pt3</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a6abdf50e71751d1a2fc25cfe45a241d6</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Pt3</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a1b4a4cb9de9e47f8e0702dd7ac6e1fa7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Pt3 &amp;</type>
      <name>operator=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a88c18a0c6340375fc67c669df9793776</anchor>
      <arglist>(const U &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>const Pt3 &amp;</type>
      <name>operator=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>aa63de8a45a609b9d6486c313a22a095b</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>const Pt3 &amp;</type>
      <name>operator=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>af5fd3b959ddde343b38a9aaacabef6d9</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>const Pt3 &amp;</type>
      <name>operator=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>adc7f51b8ce714d392ce78556ad8aff62</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>af2a2b4805862eb440dbcd394cd36678e</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a5ba6b67959c50afd69e68eca154643c7</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>afdff7850f77c536fa68f317efd69b7a4</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a98187b41706edcf6a38894669292edec</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a359d6001d3d09d468abe2288a3529fe3</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a00314e5f8cada621d2ed87e14343e88e</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a9b8351888cfdc8eb66c73462759c139a</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>aca5be172a7e12ba497ac10fd001e4442</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>ab8b60dfc4939adffb5517607f1881377</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>ab53436d35faadc2945e41757de058108</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a8ad152b975fabed5c39459b3743db167</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>ad62ff46855b323c464e8527551584c83</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>ade318979f8b9afe1778b1c1df00cd628</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a86bcf0c0f900604f856ec5df70447e0e</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a7608685f25ef449500fb9f6abe8953e1</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a5c8e26a33bb700204f331afab33161cb</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a151ed5c02719cea34571b21c31f6b0b1</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>af9c5c2d59fb2935c744c964c59bbddce</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>aabd344a1c2906617320157bf1202853c</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a70bf13c0718f2a278fe5facc0c8cebfc</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a57b9c3239171d5eb83d2101f00e693b6</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a69a52f4cc58d92ab412a85fefe7e7812</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a1aa935ad156ffb623ef5e476542a9979</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a66159fff9e3ef75073aa90fb3b48b318</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt3</type>
      <name>operator+</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a12f67e56e04e520414eeee1bec541d35</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt3</type>
      <name>operator+</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>ac6077a6521372229af524cd50cdd6da8</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt3</type>
      <name>operator+</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>acec50c61924f9ee1cb04d4688c26a511</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt3</type>
      <name>operator+</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a96725aef94f0a7fd1b92c7d534bed2de</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt3</type>
      <name>operator-</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a5fe55cb27ac7d4eb3c0c5b6a4121f738</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt3</type>
      <name>operator-</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>ae39c78f06e08dbf34ca19881ae2b6439</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt3</type>
      <name>operator-</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>adb3f456d8a7e850972b4743d18c5df6b</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt3</type>
      <name>operator-</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a8f187824f71faad021fb9fb8631cc8e5</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt3</type>
      <name>operator-</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>ae0d2b8ed583d14c20e27952854257819</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Pt3</type>
      <name>operator*</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a1a7b90d39dd11ed220e8d2f87c8ff719</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt3</type>
      <name>operator*</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>aa0df898ee90438428075eb9307165865</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt3</type>
      <name>operator*</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>ad99aea92c53b2e5c193d90b665312a47</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt3</type>
      <name>operator*</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>ad24a36761e8a8afda268a232a75abcfe</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt3</type>
      <name>operator/</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>adfcd24fc9d0891bd835ae311ffcb066e</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt3</type>
      <name>operator/</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a87a4e5b7f1076275501a2143533e3478</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt3</type>
      <name>operator/</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a0672ffd4091804a4135a07c6d3ff4af8</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt3</type>
      <name>operator/</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a84981aed952d08926bb57515d5e75228</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator+=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a648bcc2b75e297ede0e2d49686418506</anchor>
      <arglist>(const U &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator+=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a81d732847bf2130f31eb1359eb5b2800</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator+=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a3999a04fc1b51ad9db30b732ff65e2e1</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator+=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a7f5ed45d100ce058e7a0ce8aa920f977</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator-=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>acf04ceb183d039fdfa63a3ca50cd6378</anchor>
      <arglist>(const U &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator-=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>acd16fc6f015bd05e724624dd6f25ffbc</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator-=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a16cba5882b2c58557f9336e07c7a439b</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator-=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a71730b6e732bd39c0ce237a8082ba42c</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator*=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>af1189dd45597028737345b1a56a7f6c3</anchor>
      <arglist>(const U &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator*=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a2642fe353bc8469707b38f01b44c713c</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator*=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a559f1e10d68751b171125b60842699f5</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator*=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a78f4af43ec065f67a35545b96803a18d</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator/=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>aa06def60c9c07bf3347ea03d9beddaea</anchor>
      <arglist>(const U &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator/=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>aca7858c91a12b57dbcd41b51a28a3bbe</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator/=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a09decd1af18fc605cd7a2e29dcdcaafd</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator/=</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>af5f40173bfe3ba7adb399703c66563e0</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Set</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a4703ba1475fe6eb8bb981b3f6f0f2854</anchor>
      <arglist>(T a_x, T a_y, T a_z)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Set</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a8946bec2a3b82c9a394a28008a55d118</anchor>
      <arglist>(T a)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>operator[]</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>ae4eaaae58dbf1cd04fb13164ea5362c6</anchor>
      <arglist>(unsigned int a) const </arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>operator[]</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>af5ae20bc3fa46f631488f4e942a1e11d</anchor>
      <arglist>(unsigned int a)</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>at</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a5a6aaef219de3d28c93d66994f99160f</anchor>
      <arglist>(unsigned int a) const </arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>at</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>adc79fb88c6126b8c1d3477f851c49bfa</anchor>
      <arglist>(unsigned int a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>serialize</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>adb7ca06b5d0c237afa77aa7c183477a4</anchor>
      <arglist>(Archive &amp;archive, const unsigned int version)</arglist>
    </member>
    <member kind="variable">
      <type>T</type>
      <name>x</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a3870f08593cabc47fd5d213ea1c0898a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>T</type>
      <name>y</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>a218217ff3405493c7b6dce94935f1290</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>T</type>
      <name>z</name>
      <anchorfile>classxms_1_1_pt3.html</anchorfile>
      <anchor>af018fc0ba7dcbb74142c9a3ddadf5610</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::Pt4</name>
    <filename>classxms_1_1_pt4.html</filename>
    <templarg>T</templarg>
    <member kind="function">
      <type></type>
      <name>Pt4</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a3449555713ec1979640a1fafbec9103d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Pt4</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a8e10bdc1272f19a02218b6e529b6a3a6</anchor>
      <arglist>(T a_x, T a_y, T a_z, T a_w)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Pt4</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a6e6ddfff5ba0abc31ffee2df02f1776b</anchor>
      <arglist>(T a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Pt4</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a45b892620539ec8566ed558c33c7c811</anchor>
      <arglist>(const Pt4 &amp;a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Pt4</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a408d8576e123c30dc47aa09d9e89fc19</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Pt4</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a40e85a1086da35a72a4e3d6cc7c559f5</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Pt4</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>ac1e55f79a0e5f38c57c12e9b007ac5f2</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Pt4</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a5cd39733ccb240f7c9c10f3569d2f2bd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Pt4 &amp;</type>
      <name>operator=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a4868f688b2e42ee007a83d8020dab7ef</anchor>
      <arglist>(const U &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>const Pt4 &amp;</type>
      <name>operator=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a221c38d4ab6aa5dd5c94a4d68b6d6bb7</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>const Pt4 &amp;</type>
      <name>operator=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a9cae65ea75f2bc634a29ff4175b7f478</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>const Pt4 &amp;</type>
      <name>operator=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a03ef7c449cd3e6f26bd2879fba1747da</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>ac84d35da8880de9c3530ce735d03cf66</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>aaaa97a0768418b3ff70f4bc9e4951caf</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a98615ce7cdfb6b9a531eb02b8f1253b7</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a7a230f6124bdc95c95d369bebdcb69a4</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a57e0ca244541713a1927eaa38626f1cd</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a5dca412d24ad064affef04a2c2bbee0e</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>ac14805f7b769fb3d78289ea8120e953d</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a4b22095940cf9cb21242dc7ae544ce02</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a4f99e9205d8cd2ad1012f2ebf58cd7f3</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a55121f6e0834607a3894170e0d6848b8</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>af8c65f43d180e67394b643272d9fbfd4</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a8361350bc56865382e690c7a3a1f8a75</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a234545de1999aceb1261c72f8ad5cc6f</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a60d3930a11151790f08662665e64eceb</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>ad638ea896571c9ffee0477a59a8c4cd2</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a7f44d2364148147e4bd2e99c503bf84c</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a4e5be48ffbafd7f34a2b56fb7fe8fe94</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a8e4fe0911ccc6068d430ee6ab87145c2</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>aea4582e226c3400945ef43ea303f1938</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>ac686f176b97c8145bf916d10cee0ce95</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a447b90070d97ea3b3869aabda4a90c9b</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>ad5d6053f7121968cd7926a2a168677d1</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a11d3def9b4c81150cb9e590deb6d6288</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>aa9a8d1b393cfa6f6082e4b08851312fc</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt4</type>
      <name>operator+</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a7f426054e233b190f79b559ea0ed6cf7</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt4</type>
      <name>operator+</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a078c1ced6ee2b7dce86ef20a01327f3a</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt4</type>
      <name>operator+</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a4e82e4e90bb61f4fb9737fbb53dec0f5</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt4</type>
      <name>operator+</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a89ab182c9b5d4f5d07d0b2a190ef5d20</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt4</type>
      <name>operator-</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a681534ace524368e4fe2133a40327e3c</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt4</type>
      <name>operator-</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a6263db5973ed2bc03bd357c4d7d8b7a2</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt4</type>
      <name>operator-</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a56f9b0fdeab9c48cc550eeaa4b67fcb7</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt4</type>
      <name>operator-</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>af46052b9e063407c1b146bb3cfd8f0ee</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt4</type>
      <name>operator-</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a34cbdaeb34d6387cf2659b05d7ddffb5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Pt4</type>
      <name>operator*</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a9d600c5f7e6e4885a56c7057f48163ee</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt4</type>
      <name>operator*</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>aed723023562ceca8528406aad8b32c14</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt4</type>
      <name>operator*</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a1debbf69117d2aedf5f4d64ec481d4a1</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt4</type>
      <name>operator*</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a58d99213e45623cc7e178eb596856c9b</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt4</type>
      <name>operator/</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a0b0ad7563bd37696abe9089dff7d02fe</anchor>
      <arglist>(const U &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt4</type>
      <name>operator/</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a26631680f760b12898cc15e7a081b587</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt4</type>
      <name>operator/</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>ab85024759092a85c171517a556da4cc1</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>Pt4</type>
      <name>operator/</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>aded55c431b7d558d692721486219988c</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator+=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a4eed05e0907b18818e1240e5ffc8bb7f</anchor>
      <arglist>(const U &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator+=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a0a2d77f197ad283aa7cae82ba15afe1f</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator+=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a2e4440e5874d4771218e51718353f5bb</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator+=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a181ce27ecf9d3a0613b3e9168631f97f</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator-=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>ae9d64f737a2274b1795ecccffddbbe8a</anchor>
      <arglist>(const U &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator-=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>ae84e096f75c8dcd04dd2a77e78dca2f7</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator-=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a98123d29e55e2c7091bbd2209493227a</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator-=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a0c669185c52efeb23cb3b4865fd6f646</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator*=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a0659b7115dc185bb3f1b029afff10f60</anchor>
      <arglist>(const U &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator*=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>ab64a8cb7a4893429afae271afa86d4a6</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator*=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>abe888d7798203dd76fea694c7faca4ed</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator*=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>ae441ef3e625aa9cadbe64a817ee535e7</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator/=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>ae307d843bea8d3b3f310847d23f1ad15</anchor>
      <arglist>(const U &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator/=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>af453c13aced9e493e6a093734bdb52d6</anchor>
      <arglist>(const Pt2&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator/=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a0317081b250e4f55459ee28fe9ed4ac4</anchor>
      <arglist>(const Pt3&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator/=</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a0de6ed18e51492e89d8eb33510b94d00</anchor>
      <arglist>(const Pt4&lt; U &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Set</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>af674dee3343d0a267d8b187642feccae</anchor>
      <arglist>(T a_x, T a_y, T a_z, T a_w)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Set</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>ad48dd5e1f867c2aff334c7f5d8049089</anchor>
      <arglist>(T a)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>operator[]</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>ae3eac9b70cc2abfe77c6bd53478a9de3</anchor>
      <arglist>(unsigned int a) const </arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>operator[]</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>aa21f1a9c08d97ae658e44bda8d3fbfcd</anchor>
      <arglist>(unsigned int a)</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>at</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a2d9491da7438d1001a9bb46868bc601a</anchor>
      <arglist>(unsigned int a) const </arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>at</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>abf51f7ef5e08f736dcba70693b6f4be6</anchor>
      <arglist>(unsigned int a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>serialize</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>ab5f8403d5b07eaede50f22e6172b927c</anchor>
      <arglist>(Archive &amp;archive, const unsigned int version)</arglist>
    </member>
    <member kind="variable">
      <type>T</type>
      <name>x</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>aad37780e1c7e2ee393de407fb197b8f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>T</type>
      <name>y</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>abf1e472e85eee6a9b9767e0bbfe1b141</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>T</type>
      <name>z</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a183571931c83bf28eb6d5741f091ee6a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>T</type>
      <name>w</name>
      <anchorfile>classxms_1_1_pt4.html</anchorfile>
      <anchor>a871dee21ccefe470143d40290306b2c8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::PublicObserver</name>
    <filename>classxms_1_1_public_observer.html</filename>
    <base>xms::Observer</base>
    <member kind="function" protection="private">
      <type>void</type>
      <name>OnProgressStatus</name>
      <anchorfile>classxms_1_1_public_observer.html</anchorfile>
      <anchor>a59f5291eaa7a6710f0cddbb95208d18e</anchor>
      <arglist>(double a_percentComplete) override</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>OnBeginOperationString</name>
      <anchorfile>classxms_1_1_public_observer.html</anchorfile>
      <anchor>a3eb61c2632b4a8d026d3fb72bf3ad756</anchor>
      <arglist>(const std::string &amp;a_operation) override</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>OnEndOperation</name>
      <anchorfile>classxms_1_1_public_observer.html</anchorfile>
      <anchor>a8da922214a2449d4fabbb339b160ec2f</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>OnUpdateMessage</name>
      <anchorfile>classxms_1_1_public_observer.html</anchorfile>
      <anchor>ac640bbab949fc3325b75fd56df6ef67e</anchor>
      <arglist>(const std::string &amp;a_message) override</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>TimeRemainingInSeconds</name>
      <anchorfile>classxms_1_1_public_observer.html</anchorfile>
      <anchor>a272bd0d80acc3fc269528ff88ca8bfb4</anchor>
      <arglist>(double a_remainingSeconds) override</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>TimeElapsedInSeconds</name>
      <anchorfile>classxms_1_1_public_observer.html</anchorfile>
      <anchor>aefde702d3859c6e6ff376122528dc4aa</anchor>
      <arglist>(double a_elapsedSeconds) override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::ETestMessagingState</name>
    <filename>classxms_1_1_e_test_messaging_state.html</filename>
    <member kind="function">
      <type></type>
      <name>ETestMessagingState</name>
      <anchorfile>classxms_1_1_e_test_messaging_state.html</anchorfile>
      <anchor>a90828ce997911657701af863ffde668c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetDefault</name>
      <anchorfile>classxms_1_1_e_test_messaging_state.html</anchorfile>
      <anchor>affaa1f5cc69a0ba6fcd4fd12b87e69ea</anchor>
      <arglist>(int a_)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ClearDefault</name>
      <anchorfile>classxms_1_1_e_test_messaging_state.html</anchorfile>
      <anchor>aade9d4c6d37ea3d95c689ae38a757ed8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetDefault</name>
      <anchorfile>classxms_1_1_e_test_messaging_state.html</anchorfile>
      <anchor>a576bc48a3eccc9f7fd55fcafdd8bd8f8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetSkipping</name>
      <anchorfile>classxms_1_1_e_test_messaging_state.html</anchorfile>
      <anchor>a7f2f1bc288a6a4a7f9b75c3d478668ea</anchor>
      <arglist>(bool a_)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetSkipping</name>
      <anchorfile>classxms_1_1_e_test_messaging_state.html</anchorfile>
      <anchor>a5e54c4195f23b5d7ac9eb51c76ffa79a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>DefaultValWasSet</name>
      <anchorfile>classxms_1_1_e_test_messaging_state.html</anchorfile>
      <anchor>adc5d8d8b958ecb0f95a901c9b819054e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>m_skippingMessages</name>
      <anchorfile>classxms_1_1_e_test_messaging_state.html</anchorfile>
      <anchor>abfa35b994a6cee56d26b28ce9d98e4b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>m_defaultSet</name>
      <anchorfile>classxms_1_1_e_test_messaging_state.html</anchorfile>
      <anchor>a57c93fd4ad19f66cab6fe93169eb3df2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>m_defaultRetValue</name>
      <anchorfile>classxms_1_1_e_test_messaging_state.html</anchorfile>
      <anchor>a1a316eaebf330b2b8a055357a6dda843</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="dir">
    <name>/home/travis/build/Aquaveo/xmscore/xmscore/math</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/math/</path>
    <filename>dir_79150a5dd4786a4a64bd739ebe6d8d7f.html</filename>
    <file>math.cpp</file>
    <file>math.h</file>
    <file>math.t.h</file>
  </compound>
  <compound kind="dir">
    <name>/home/travis/build/Aquaveo/xmscore/xmscore/python/misc</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/python/misc/</path>
    <filename>dir_4881bc6934a7205147f4e3dcb0171f6e.html</filename>
    <file>__init__.py</file>
    <file>misc_py.cpp</file>
    <file>misc_py.h</file>
    <file>observer_py.cpp</file>
    <file>observer_pyt.py</file>
    <file>PublicObserver.h</file>
    <file>PyObserver.h</file>
    <file>PyUtils.cpp</file>
    <file>PyUtils.h</file>
  </compound>
  <compound kind="dir">
    <name>/home/travis/build/Aquaveo/xmscore/xmscore/misc</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/misc/</path>
    <filename>dir_17175abc7be81dc32d09e65ff06b8825.html</filename>
    <file>base_macros.h</file>
    <file>boost_defines.h</file>
    <file>carray.h</file>
    <file>color_defines.h</file>
    <file>DynBitset.cpp</file>
    <file>DynBitset.h</file>
    <file>environment.h</file>
    <file>Observer.cpp</file>
    <file>Observer.h</file>
    <file>Observer.t.h</file>
    <file>Progress.cpp</file>
    <file>Progress.h</file>
    <file>Progress.t.h</file>
    <file>Singleton.cpp</file>
    <file>Singleton.h</file>
    <file>StringUtil.cpp</file>
    <file>StringUtil.h</file>
    <file>StringUtil.t.h</file>
    <file>XmConst.h</file>
    <file>XmError.cpp</file>
    <file>XmError.h</file>
    <file>XmError.t.h</file>
    <file>XmLog.cpp</file>
    <file>XmLog.h</file>
    <file>XmLog.t.h</file>
    <file>xmstype.h</file>
  </compound>
  <compound kind="dir">
    <name>/home/travis/build/Aquaveo/xmscore/xmscore/points</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/points/</path>
    <filename>dir_23f3c927444a6adb7b8d9e2e971871ec.html</filename>
    <file>functors.cpp</file>
    <file>functors.h</file>
    <file>functors.t.h</file>
    <file>pt.cpp</file>
    <file>pt.h</file>
    <file>pt.t.h</file>
    <file>ptsfwd.h</file>
  </compound>
  <compound kind="dir">
    <name>/home/travis/build/Aquaveo/xmscore/xmscore/python</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/python/</path>
    <filename>dir_f6932f4423028a8b1120450691f3eef1.html</filename>
    <dir>/home/travis/build/Aquaveo/xmscore/xmscore/python/misc</dir>
    <file>__init__.py</file>
    <file>cxxtest.cpp</file>
    <file>xmscore_py.cpp</file>
  </compound>
  <compound kind="dir">
    <name>/home/travis/build/Aquaveo/xmscore/xmscore/stl</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/stl/</path>
    <filename>dir_7215248b9fd9b286115742ce43a743df.html</filename>
    <file>deque.h</file>
    <file>hash.h</file>
    <file>list.h</file>
    <file>map.h</file>
    <file>set.h</file>
    <file>utility.h</file>
    <file>vector.cpp</file>
    <file>vector.h</file>
  </compound>
  <compound kind="dir">
    <name>/home/travis/build/Aquaveo/xmscore/xmscore/testing</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/testing/</path>
    <filename>dir_2c2e060d770fb9750ac9f3b9b695c5a0.html</filename>
    <file>TestTools.cpp</file>
    <file>TestTools.h</file>
  </compound>
  <compound kind="dir">
    <name>/home/travis/build/Aquaveo/xmscore/xmscore</name>
    <path>/home/travis/build/Aquaveo/xmscore/xmscore/</path>
    <filename>dir_6cdcad1f5e4081dc72dc4b275cda5426.html</filename>
    <dir>/home/travis/build/Aquaveo/xmscore/xmscore/math</dir>
    <dir>/home/travis/build/Aquaveo/xmscore/xmscore/misc</dir>
    <dir>/home/travis/build/Aquaveo/xmscore/xmscore/points</dir>
    <dir>/home/travis/build/Aquaveo/xmscore/xmscore/python</dir>
    <dir>/home/travis/build/Aquaveo/xmscore/xmscore/stl</dir>
    <dir>/home/travis/build/Aquaveo/xmscore/xmscore/testing</dir>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title></title>
    <filename>index</filename>
    <docanchor file="index" title="xmscore ">xmscore</docanchor>
    <docanchor file="index" title="Introduction ">XmscoreIntroduction</docanchor>
    <docanchor file="index" title="License ">XmscoreLicense</docanchor>
    <docanchor file="index" title="Testing ">XmscoreTesting</docanchor>
    <docanchor file="index" title="The Code ">XmscoreTheCode</docanchor>
    <docanchor file="index" title="Namespaces">XmscoreNamespaces</docanchor>
    <docanchor file="index" title="&quot;xmscore&quot; Name ">xmscoreName</docanchor>
  </compound>
</tagfile>
