//
// Copyright (c) 1993-2022 Robert McNeel & Associates. All rights reserved.
// OpenNURBS, Rhinoceros, and Rhino3D are registered trademarks of Robert
// McNeel & Associates.
//
// THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
// ALL IMPLIED WARRANTIES OF FITNESS FOR ANY PARTICULAR PURPOSE AND OF
// MERCHANTABILITY ARE HEREBY DISCLAIMED.
//
// For complete openNURBS copyright information see <http://www.opennurbs.org>.
//
////////////////////////////////////////////////////////////////

#include "opennurbs.h"

#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined 
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif

#include "opennurbs_subd_data.h"

/////////////////////////////////////////////////////////
//
// Built-in quad subdivision
//

static double eigenvalue_cos(unsigned int k, unsigned int N)
{
  double a = ((double)k) / ((double)N);

  if (2 * k > N)
  {
    ON_SubDIncrementErrorCount();
    ON_ERROR("bogus k");
  }

  double cos_pia = cos(a*ON_PI);
  // 0 <= k <= N/2

  // cos(0) = 1
  // cos(pi/6) = sqrt(3)/2
  // cos(pi/4) = 1/sqrt(2)
  // cos(pi/3) = 1/2
  // cos(pi/2) = 0
  if (0 == k)
    cos_pia = 1.0;
  else if (6 * k == N)
    cos_pia = (0.5*sqrt(3));
  else if (4 * k == N)
    cos_pia = sqrt(0.5);
  else if (3 * k == N)
    cos_pia = 0.5;
  else if (2 * k == N)
    cos_pia = 0.0;

  return cos_pia;
}

static void GetQuadSubdivisionMatrix_eigenvalue_pair(
  unsigned int k,
  unsigned int N,
  double* eigenvalues
  )
{
  // 0 <= k <= N, N >= 3

  // a = 2*pi*k/N
  // lambdas = (5 + cos(a) +/- cos(a/2)*sqrt(18 + 2*cos(a)))/16


  // Use cos(a) = cos(2pi - a) and cos(pi/2 + a) = cos(pi/2 - a)
  // to limit all cosine evaluations to 0 <= a <= pi/2. This
  // insures that eigenvalues that are theoretically equal
  // get the same value when stored in a double.

  // c1 = cos(2*pi*k/N) = sign1*cos(pi*k1/N)
  // c2 = cos(pi*k/N) = sign2*cos(pi*k2/N);
  double sign1, sign2;

  unsigned int k1 = 2 * k;
  if (k1 > N)
    k1 = 2 * N - k1;
  // cos(pi*k1/N) = cos(2pi*k/N) 

  if (2 * k1 > N)
  {
    sign1 = -1.0;
    k1 = N - k1;
  }
  else
  {
    sign1 = 1.0;
  }

  // cos(pi*k2/N) = cos(pi*k/N);
  unsigned int k2 = k;
  if (2 * k2 > N)
  {
    sign2 = -1.0;
    k2 = N - k2;
  }
  else
  {
    sign2 = 1.0;
  }

  double c1 = sign1*eigenvalue_cos(k1, N);
  double c2 = sign2*eigenvalue_cos(k2, N);

  if (fabs(c1 - cos(2.0*(ON_PI*k / ((double)N)))) > 1e-6)
  {
    ON_ERROR("bogus c1");
  }

  if (fabs(c2 - cos(ON_PI*k / ((double)N))) > 1e-6)
  {
    ON_ERROR("bogus c2");
  }

  double x = 5.0 + c1;
  double y
    = 3.0*((4 * k2 == N)
    ? (((c2 < 0.0) ? -1.0 : 1.0)*sqrt(1.0 + c1 / 9.0))
    : c2*sqrt(2.0 + c1 / 4.5));

  eigenvalues[0] = 0.0625*(x - y);
  eigenvalues[1] = 0.0625*(x + y);

  double lambda0 = (5.0 + c1 - c2*sqrt(18.0 + 2.0 * c1)) / 16.0;
  double lambda1 = (5.0 + c1 + c2*sqrt(18.0 + 2.0 * c1)) / 16.0;

  if (fabs(lambda0 - eigenvalues[0]) > 1e-6)
  {
    ON_ERROR("bogus lambda0");
  }

  if (fabs(lambda1 - eigenvalues[1]) > 1e-6)
  {
    ON_ERROR("bogus lambda1");
  }

}

static unsigned int GetQuadCreaseEigenvalues(
  unsigned int N,
  unsigned int R,
  double* eigenvalues
)
{
  static const double e2[4] = 
  {1.0, 0.5, 0.25, 0.25};
  static const double e3[6] = 
  {1.0, 0.5, 0.5, 0.25, 0.25, 0.125};
  static const double e4[8] = 
  {1.0, 0.5, 0.5, 0.3475970508005518921819191, 0.25, 0.25,
  0.08990294919944810781808094, 0.0625};
  static const double e5[10] = 
  {1.0, 0.5, 0.5, 0.4027739218546748178592416, 0.2985112089851678742713826, 0.25,
  0.25, 0.06132374806987680407830079, 0.04544938284868830104054729,
  0.03661165235168155944989445};
  static const double e6[12] = 
  {1.0, 0.5, 0.5, 0.4338607343486338835457207, 0.3500160863488253415435189,
  0.2788059129733551205593399, 0.25, 0.25, 0.0428127141360395954023001,
  0.0341025407605693744181211, 0.02751214135449768844149263,
  0.02387287570313157198721332};
  static const double e7[14] = 
  {1.0, 0.5, 0.5, 0.4524883960194854484584697, 0.3868484484678842764124981,
  0.3198112959966680476694149, 0.269127266963170621672735, 0.25, 0.25,
  0.03111320661766488579086877, 0.02618235305722229063965432,
  0.02164520058600606189657112, 0.01850525303440488985059954,
  0.0167468245269451691545346};
  static const double e8[16] = 
  {1.0, 0.5, 0.5, 0.4643651755137316635248271,
  0.4125707561012937086818205,
  0.3544821369293089604984253,
  0.3012775591854784677914885,
  0.2636617247210804425225423, 0.25, 0.25,
  0.02347494981551238513891938,
  0.02054399860657505933386027,
  0.01746052935054695740643632,
  0.01500214366764081029526673,
  0.01332883274300524623177295,
  0.01237889151219760922048721};
  static const double e9[18] = 
  {1.0, 0.5, 0.5, 0.4723463441863384015192462,
  0.4308226511075866703470591,
  0.3815615404738973077099547,
  0.3318586781599466572198922,
  0.2891905790294515501929928,
  0.2602656637115420192311205, 0.25, 0.25,
  0.01827951159672544722081085,
  0.01645119019440832022485581,
  0.01433600966659543228200454,
  0.01246857639828100325799948,
  0.01104289481022786208695261,
  0.01007212033415834999881356,
  0.009515058436089155483977101};
  static const double e10[20] = 
  {1.0, 0.5, 0.5, 0.4779461323788179580284805,
  0.4440893381762303346169582,
  0.4024164222230339077518639,
  0.3578375190704969729339551,
  0.3156351744644154185583903,
  0.2809030992590270743668487,
  0.2580062768878958596628428, 0.25, 0.25,
  0.0146089903173884963168662,
  0.01341819015462357521932491,
  0.0119416703391074854280824,
  0.01053330352465963744605301,
  0.009366444788855289841073367,
  0.008487506627292569369514451,
  0.00788626781457720035829123,
  0.00753842240176145199323634};
  static const double e11[22] = 
  {1.0, 0.5, 0.5, 0.4820168104737422559487429, 0.453970779385004836126948,
  0.4185545871310304361025496, 0.3791682984415772365648197,
  0.3396012178854845423282521, 0.3036900507512289303420477,
  0.2749846048497542572933016, 0.256424494661140823867932, 0.25, 0.25,
  0.01192931172817658658840325, 0.0111241417795889216648019,
  0.01007266363842353548275418, 0.009007528743858636629851362,
  0.0080675724846343704060705, 0.007308408092049598881127255,
  0.00673824807776591199003043, 0.006346184749337779034933979,
  0.006117935463105803485445083};
  static const double e12[24] = 
  {1.0, 0.5, 0.5, 0.4850641610369383823975897,
  0.4614985474347087619667882,
  0.4311821255710073423107508,
  0.3965315266016385362937548,
  0.3603110020217894833299555,
  0.3254201240117244451121387,
  0.2946777837281643548152523,
  0.270614738818649360997862,
  0.2552725419984611848187261, 0.25, 0.25,
  0.009917592896102293972385845,
  0.009355326173828645421819572,
  0.008591381125050664705040022,
  0.007779755959415404224109989,
  0.007026399790425526641978355,
  0.006384584778897758789127306,
  0.00587150765060411340781648,
  0.005485800904827523567735387,
  0.005219287163334916237544707,
  0.005063378298187826263703993};
  static const double e13[26] = 
  {1.0, 0.5, 0.5, 0.4874023599648010128335877, 0.4673500587464579739048183,
  0.4411915336267357444040795, 0.4106853584910705583143491,
  0.3778828393545584232161755, 0.3449931832638130534338588,
  0.3142414753967076886176823, 0.2877286532750699869095651,
  0.2672980989570970429233383, 0.2544068297436071576795717, 0.25, 0.25,
  0.008370985397992234789274648, 0.007967268997581054543760475,
  0.007401542504344500852893572, 0.006777068031025239694881906,
  0.006172979526104779585092999, 0.005635704073174505096388671,
  0.005185565574477465291827455, 0.00482700980099718390848469,
  0.004556832329593394957851468, 0.004369358935986746324441877,
  0.0042592717138664641562821};
  static const double e14[28] = 
  {1.0, 0.5, 0.5, 0.4892343474885726073240006,
  0.4719804834258717874763822,
  0.4492298614073128369092644,
  0.42228946574606179458229,
  0.3927069701810019940266986,
  0.362183044731843177171771,
  0.3324764840394177067868378,
  0.3053079120274184419879482,
  0.2822665844803848275730051,
  0.2647220004036752431982968,
  0.2537393296624997399764198, 0.25, 0.25,
  0.00715748880273074983971188,
  0.00686054203316051302491066,
  0.006434117641714528308420467,
  0.005948540274674075908830307,
  0.005462450723752333177711865,
  0.005014415879728434370349952,
  0.004624660494400380852689325,
  0.004300690777742151874669176,
  0.004042777577568631615465928,
  0.003847905739002843063701085,
  0.003712201361565622874300741,
  0.003632272821743496605377215};
  static const double e15[30] = 
  {1.0, 0.5, 0.5, 0.4906956940465353267709958,
  0.4757028727019528632086783,
  0.455766067824132773843117,
  0.4318751128950106685349497,
  0.4052160522897933526263431,
  0.3771127514616678985622512,
  0.3489624347972032671084194,
  0.322168625035827813472657,
  0.2980747069657881557286016,
  0.2779003551379126765050381,
  0.2626814932568613771801873,
  0.2532135590826550284758983, 0.25, 0.25,
  0.00618847384916111889230231,
  0.005965420209880330285766977,
  0.005638731508127695651873455,
  0.005257089756414251201239889,
  0.004863929529021519713339058,
  0.004490470412801530600934818,
  0.004155270492876199683215923,
  0.003867086409290046155236813,
  0.003628376449228194769988451,
  0.003438179362753015717975701,
  0.00329408456109496112534435,
  0.003193436395811162253984047,
  0.00313401097727204912273354};
  static const double e16[32] = 
  {1.0, 0.5, 0.5, 0.4918796373911240560348713,
  0.4787373551247809344061374,
  0.4611427069644219962279705,
  0.4398580642032740903608299,
  0.4158055761130113066382872,
  0.390027416834009389044947,
  0.3636412108488202632024345,
  0.3377927419491292896466998,
  0.3136080620499505782036071,
  0.292146813032174258103034,
  0.274357897741047252333337,
  0.2610378215649526154634098,
  0.2527918855047203998444193, 0.25, 0.25,
  0.005402764220102485932368158,
  0.005232096046270863116682577,
  0.004978077778632910171734617,
  0.004674960989517055686540183,
  0.004355037766598012314251226,
  0.00404323357055087285837187,
  0.003755831059271643390444508,
  0.003501740890995885397890572,
  0.003284648000405711892357816,
  0.003105035613274500157028433,
  0.002961718646983871018171953,
  0.002852868988636084124507635,
  0.002776644630749646420752988,
  0.002731549908274295258929157};
  static const double e17[34] = 
  {1.0, 0.5, 0.5, 0.4928519465484388397628774,
  0.4812419214171066989423527,
  0.4656128029920844325827301,
  0.4465606941843988484692585,
  0.424812165480439064558305,
  0.4011966249932869370793232,
  0.3766149590426153432153104,
  0.3520057408143481537617202,
  0.3283103707443307886219883,
  0.3064384408280979168009157,
  0.2872343561627713321664122,
  0.2714458174511992239759956,
  0.2596943795921930616164232,
  0.2524484295514478534381793, 0.25, 0.25,
  0.004757090297340728139502408,
  0.004624358743088481586008327,
  0.004424160910175009107610274,
  0.004180976088102615001936721,
  0.003918959943644192824684854,
  0.00365788010922537763040869,
  0.003411648832828200475698599,
  0.003188720856577044503144021,
  0.002993345157921484120166864,
  0.002826943464389544626206934,
  0.002689264842243817342049787,
  0.002579224555426395685829897,
  0.00249546001990384341095027,
  0.002436674914664392471599904,
  0.00240183994959619385922722};
  static const double e18[36] = 
  {1.0, 0.5, 0.5, 0.4936600572298639301751713,
  0.4833321071081027545791269,
  0.4693655637489887341991605,
  0.4522328837092091861166156,
  0.4325135619763201089802969,
  0.4108745595057475305920414,
  0.3880478731496155426360755,
  0.3648060650769540190542029,
  0.3419366335423175665278088,
  0.320216108508285892492672,
  0.3003846672037622620284949,
  0.2831218712479197365270371,
  0.2690238699263027046806524,
  0.2585822504755439455599121,
  0.2521649077398439413425099, 0.25, 0.25,
  0.004220179878692891801759286,
  0.004115445927936134297961187,
  0.003955713186520081732092417,
  0.003758739178522429411908854,
  0.003542728327855244753694386,
  0.003323322098671379512283609,
  0.003112217777696630959319223,
  0.002917115069157786970353485,
  0.002742396862321762198393639,
  0.00259003933228738277985616,
  0.002460457574771729873773056,
  0.002353170917222417960220722,
  0.002267275982618210720919093,
  0.002201759937123569867153837,
  0.002155696524705100825980994,
  0.002128362539512277714756394};
  static const double e19[38] = 
  {1.0, 0.5, 0.5, 0.494338860883546070532964,
  0.4850938522059087731405798,
  0.4725442488309184925419464,
  0.457069112822645281805701,
  0.4391358254141653594145081,
  0.4192859786862247557426383,
  0.3981190803632466700566333,
  0.376274597652746018210246,
  0.3544129175605437659005613,
  0.333195821913103737936705,
  0.3132670521652698526535814,
  0.2952334593627969724433445,
  0.2796471003777019238459064,
  0.2669884954445580774594627,
  0.2576512096332567606306801,
  0.2519280988436448268724412, 0.25, 0.25,
  0.003768993776777150865030121,
  0.003685274515452676520870507,
  0.003556390829335076853386117,
  0.003395405979373806912108798,
  0.003216151173333596924639297,
  0.003031009581678132504732807,
  0.002849721918135655591096795,
  0.002679121978037925651288328,
  0.002523464094201966948068253,
  0.002385003592067608708145546,
  0.002264600976431821046188419,
  0.002162236332782625743806115,
  0.002077400135120119142943681,
  0.002009368305901747016666927,
  0.0019573850140940428631998,
  0.001920778461640462632113888,
  0.001899030873473992579157122};
  static const double e20[40] = 
  {1.0, 0.5, 0.5, 0.4949144741229649487947415,
  0.4865920796256587990369664,
  0.4752586491350964339113918,
  0.4612216953194131189045514,
  0.4448620526473305969505388,
  0.4266235443444738895244926,
  0.4070009705959143560203706,
  0.3865267637057714686536609,
  0.3657566942813565517893462,
  0.34525503501672240530079,
  0.3255795888907262134327553,
  0.3072669591378968612633435,
  0.2908183749503575990130514,
  0.2766862982234843174818616,
  0.2652619581329413087246701,
  0.2568639586300465015069328,
  0.251728246273788614145149, 0.25, 0.25,
  0.003386264950190495753910062,
  0.003318560306693570214981728,
  0.003213497115566963950845717,
  0.003080812251285889215138478,
  0.002931102745744173241052439,
  0.002774195246119185997058834,
  0.002618157176972010977012182,
  0.002468953239997107683296335,
  0.002330561683921314234983495,
  0.002205328627589478520754814,
  0.002094389446004944194288476,
  0.001998057886466699264485282,
  0.001916141267292168987804277,
  0.001848175283123922040090202,
  0.001793588688772172590353523,
  0.001751813424471741486263179,
  0.001722355238933792682089404,
  0.001704837074659703299686351};

  static const size_t e_sizeof[] = {
  sizeof(e2),
  sizeof(e3),
  sizeof(e4),
  sizeof(e5),
  sizeof(e6),
  sizeof(e7),
  sizeof(e8),
  sizeof(e9),
  sizeof(e10),
  sizeof(e11),
  sizeof(e12),
  sizeof(e13),
  sizeof(e14),
  sizeof(e15),
  sizeof(e16),
  sizeof(e17),
  sizeof(e18),
  sizeof(e19),
  sizeof(e20)
  };

  static const double* e[] = {
  e2,
  e3,
  e4,
  e5,
  e6,
  e7,
  e8,
  e9,
  e10,
  e11,
  e12,
  e13,
  e14,
  e15,
  e16,
  e17,
  e18,
  e19,
  e20
  };

  static size_t e_count = sizeof(e_sizeof) / sizeof(e_sizeof[0]);
  if (e_count != sizeof(e) / sizeof(e[0]))
    return ON_SUBD_RETURN_ERROR(0);

  if (N < 2)
    return ON_SUBD_RETURN_ERROR(0);
  unsigned int edex = N - 2;
  if (edex >= e_count)
    return ON_SUBD_RETURN_ERROR(0);
  if (R != e_sizeof[edex] / sizeof(double))
    return ON_SUBD_RETURN_ERROR(0);
  if (nullptr != eigenvalues)
  {
    const double* src = e[edex];
    const double* src1 = src + R;
    double* dst = eigenvalues;
    while (src < src1)
    {
      *dst++ = *src++;
    }
  }
  return R;
}

unsigned int ON_SubDSectorType::GetAllEigenvalues(
  double* eigenvalues,
  size_t eigenvalues_capacity
  )
{
  if ( 0 == eigenvalues_capacity)
    eigenvalues = nullptr;
  else
  {
    if (nullptr == eigenvalues)
      return ON_SUBD_RETURN_ERROR(0);

    for (size_t i = 0; i < eigenvalues_capacity; i++)
      eigenvalues[i] = ON_UNSET_VALUE;
  }

  if (false == IsValid())
    return ON_SUBD_RETURN_ERROR(0);

  const unsigned int R = PointRingCount();
  if ( 0  == R || (nullptr != eigenvalues && eigenvalues_capacity < R))
    return ON_SUBD_RETURN_ERROR(0);

  const ON_SubDVertexTag vertex_tag = VertexTag();
  const unsigned int N = EdgeCount();

  if (false == ON_SubD::IsValidSectorEdgeCount(vertex_tag, N))
    return ON_SUBD_RETURN_ERROR(0);

  if (ON_SubDVertexTag::Smooth == vertex_tag)
  {
    if (nullptr == eigenvalues)
    {
      // caller is asking if eigenvalues are available
      return R;
    }
    eigenvalues[0] = 1.0;

    double a = (3 * N - 7);
    double b = (N >= 6) ? ((5 * N - 30)*N + 49) : ((5 * N*N + 49) - 30 * N);
    double c = sqrt(b);
    double d = 0.125;
    unsigned int D = N;
    while (D > 0 && 0 == (D % 2))
    {
      D /= 2;
      d *= 0.5;
    }
    d /= ((double)D);

    eigenvalues[1] = d*(a + c);
    eigenvalues[2] = d*(a - c);

    for (unsigned int k = 1; k < N; k++)
    {
      double e2[2];
      GetQuadSubdivisionMatrix_eigenvalue_pair(k, N, e2);
      eigenvalues[2 * k + 1] = e2[0];
      eigenvalues[2 * k + 2] = e2[1];
    }

    // return sorted in decreasing order
    ON_SortDoubleArrayDecreasing(eigenvalues + 1, R - 1);
  }
  else if (ON_SubDVertexTag::Crease == vertex_tag)
  {
    if (N <= 20)
    {
      if (nullptr == eigenvalues)
      {
        // caller is asking if eigenvalues are available
        return R;
      }
      if (R != GetQuadCreaseEigenvalues(N, R, eigenvalues) || !(1.0 == eigenvalues[0]))
        return ON_SUBD_RETURN_ERROR(0);
    }
  }

  if (nullptr == eigenvalues)
  {
    // caller is asking if eigenvalues are available
    return 0; // not an error
  }

  if (!(1.0 == eigenvalues[0]))
    return ON_SUBD_RETURN_ERROR(0);

  return R;
}




bool ON_SubDMatrix::EvaluateCosAndSin(
  unsigned int j,
  unsigned int n,
  double* cos_theta,
  double* sin_theta
  )
{
  double cos_angle;
  double sin_angle;

  if (n < 1)
  {
    if (cos_theta)
      *cos_theta = ON_DBL_QNAN;
    if (sin_theta)
      *sin_theta = ON_DBL_QNAN;
    return ON_SUBD_RETURN_ERROR(false);
  }

#if defined(ON_DEBUG)
#define ON_DEBUG_TEST_SUBD_EVSINCOS
#endif

#if defined(ON_DEBUG_TEST_SUBD_EVSINCOS)
  const double theta_dbg = (j*ON_PI)/n;
  const double cos_dbg = cos(theta_dbg);
  const double sin_dbg = sin(theta_dbg);
#endif

  double cos_sign = 1.0;
  while ( j > n)
  {
    // cos(a) = -cos(a-pi)
    // sin(a) = -sin(a-pi)
    cos_sign *= -1.0;
    j -= n;
  }
  double sin_sign = cos_sign;

  if ( 0 == j )
  {
    // cos(0) = 1
    // sin(0) = 0
    cos_angle = cos_sign;
    sin_angle = 0.0;
  }
  else if ( n == j )
  {
    // cos(pi) = -1
    // sin(pi) = 0
    cos_angle = -cos_sign;
    sin_angle = 0.0;
  }
  else if ( 2*j == n)
  {
    // cos(pi/2) = 0
    // sin(pi/2) = 1
    cos_angle = 0.0;
    sin_angle = sin_sign;
  }
  else
  {
    if ( 2*j > n )
    {
      // cos(a) = cos(pi-a)
      // sin(a) = sin(pi-a)
      j = n-j;
      cos_sign *= -1.0;
    }
    if (6 * j == n)
    {
      // cos(a) = cos(pi/6)
      // sin(a) = sin(pi/6) 
      cos_angle = cos_sign*0.5*sqrt(3.0);
      sin_angle = sin_sign*0.5;
    }
    else if (4 * j == n)
    {
      // cos(a) = cos(pi/4)
      // sin(a) = sin(pi/4)
      const double sqrt_half = sqrt(0.5);
      cos_angle = cos_sign*sqrt_half;
      sin_angle = sin_sign*sqrt_half;
    }
    else if (3 * j == n)
    {
      // cos(a) = cos(pi/3)
      // sin(a) = sin(pi/3)
      cos_angle = cos_sign*0.5;
      sin_angle = sin_sign*0.5*sqrt(3.0);
    }
    else
    {
      const double theta = (j*ON_PI) / n;
      cos_angle = cos_sign*cos(theta);
      sin_angle = sin_sign*sin(theta);
    }
  }
#if defined(ON_DEBUG_TEST_SUBD_EVSINCOS)
  double e = fabs(cos_dbg - cos_angle) + fabs(sin_dbg - sin_angle);
  if ( e > 1e-12 )
  {
    ON_SubDIncrementErrorCount();
    ON_ERROR("Bug in SinCosEv precision improvment code.");
  }
#endif

  if (cos_theta)
    *cos_theta = cos_angle;
  if (sin_theta)
    *sin_theta = sin_angle;
  return true;
}


unsigned int ON_SubDSectorType::GetSubdivisionMatrix(
  double** S,
  size_t S_capacity
  ) const
{
  if ( S_capacity < 3 || nullptr == S )
    return ON_SUBD_RETURN_ERROR(0);

  const unsigned int R = PointRingCount();
  if (R < 3)
    return ON_SUBD_RETURN_ERROR(0);

  if ( S_capacity < R )
    return ON_SUBD_RETURN_ERROR(0);

  if (nullptr == S)
    return ON_SUBD_RETURN_ERROR(0);

  for (unsigned int i = 0; i < R; i++)
  {
    if (nullptr == S[i])
      return ON_SUBD_RETURN_ERROR(0);
  }

  const unsigned int N = EdgeCount();

  
  if (this->IsSmoothSector() || this->IsDartSector())
  {
    // April 2019 Dale Lear - Catmull Clark Valence 2 Evaluation: Smooth and Dart
    // See comments in ON_SubDSectorType::GetSurfaceEvaluationCoefficients()
    // for more details on how this case is handled.
    // Valence 2 has R = 5, N = 5
    if (N < 2 || R < 5)
      return ON_SUBD_RETURN_ERROR(0);

    /*
    Parameters:
    N - [in]
    vertex valence (>= 3)
    S - [out]
      (2N+1)x(2N+1) matrix
      (4N*N + 4N + 1) doubles
      S[0,...,2N] = first row
      S[2N+1,...,4N+1] = second row
      S[4N+2,...,6N+2] = third row
      ...
      S[4N*N + 2N,...,4N*N + 4N] = 2N+1st (last) row
    */
    const double a = 1.0 - 7.0 / (4.0*N);
    const double b = 3.0 / (2.0*N*N);
    const double c = 1.0 / (4.0*N*N);
    const double dart_factor = this->IsDartSector() ? 0.25*cos(2.0*ON_PI/((double)N)) : 0.0;
    const double d_center = 3.0 / 8.0 + dart_factor;
    const double d_ring = 3.0 / 8.0 - dart_factor;
    const double e = 1.0 / 16.0;
    const double f = 1.0 / 4.0;
    double* x;
    double* y;
    double* x1;

    if (5 == R)
    {
      if (this->IsDartSector())
      {
        // April 2019 Dale Lear - Catmull Clark Valence 2 Evaluation: Dart
        // See comments in ON_SubDSectorType::GetSurfaceEvaluationCoefficients()
        // for more details on how this case is handled.
        //
        // Dart Valence 2 subdivision matrix special case.
        S[0][0] = 1.0 / 8.0;
        S[0][1] = 3.0 / 8.0;
        S[0][2] = 1.0 / 16.0;
        S[0][3] = 3.0 / 8.0;
        S[0][4] = 1.0 / 16.0;

        // creased edge subdivision
        S[1][0] = 1.0 / 2.0;
        S[1][1] = 1.0 / 2.0;
        S[1][2] = 0.0;
        S[1][3] = 0.0;
        S[1][4] = 0.0;

        S[2][0] = 1.0 / 4.0;
        S[2][1] = 1.0 / 4.0;
        S[2][2] = 1.0 / 4.0;
        S[2][3] = 1.0 / 4.0;
        S[2][4] = 0.0;

        // smooth edge subdivision
        // k = 2, theta = 2pi/2 = pi, cos(theta) = cos(pi) = -1
        S[3][0] = 1.0 / 8.0;  // = 3/4 + cos(theta)/4
        S[3][1] = 1.0 / 8.0;  // deviates from general case because P0 is a corner of both quads attached to edge(C,P1)
        S[3][2] = 1.0 / 16.0;
        S[3][3] = 5.0 / 8.0;  // = 3/4 - cos(theta)/4
        S[3][4] = 1.0 / 16.0;

        S[4][0] = 1.0 / 4.0;
        S[4][1] = 1.0 / 4.0;
        S[4][2] = 0.0;
        S[4][3] = 1.0 / 4.0;
        S[4][4] = 1.0 / 4.0;
      }
      else
      {
        // April 2019 Dale Lear - Catmull Clark Valence 2 Evaluation: Smooth
        // See comments in ON_SubDSectorType::GetSurfaceEvaluationCoefficients()
        // for more details on how this case is handled.
        //
        // Smooth Valence 2 subdivision matrix special case.
        S[0][0] = 1.0 / 8.0;
        S[0][1] = 3.0 / 8.0;
        S[0][2] = 1.0 / 16.0;
        S[0][3] = 3.0 / 8.0;
        S[0][4] = 1.0 / 16.0;

        S[1][0] = 3.0 / 8.0;
        S[1][1] = 3.0 / 8.0;
        S[1][2] = 1.0 / 16.0;
        S[1][3] = 1.0 / 8.0;
        S[1][4] = 1.0 / 16.0;

        S[2][0] = 1.0 / 4.0;
        S[2][1] = 1.0 / 4.0;
        S[2][2] = 1.0 / 4.0;
        S[2][3] = 1.0 / 4.0;
        S[2][4] = 0.0;

        S[3][0] = 3.0 / 8.0;
        S[3][1] = 1.0 / 8.0;
        S[3][2] = 1.0 / 16.0;
        S[3][3] = 3.0 / 8.0;
        S[3][4] = 1.0 / 16.0;

        S[4][0] = 1.0 / 4.0;
        S[4][1] = 1.0 / 4.0;
        S[4][2] = 0.0;
        S[4][3] = 1.0 / 4.0;
        S[4][4] = 1.0 / 4.0;
      }
    }
    else
    {
      // first row
      x = S[0];
      *x++ = a;
      x1 = x + R;
      while (x < x1)
      {
        *x++ = b;
        *x++ = c;
      }

      // second row
      x = S[1];
      x1 = x + R - 2;
      *x++ = d_center;
      const double* E = x;
      *x++ = d_ring;
      *x++ = e;
      *x++ = e;
      while (x < x1)
        *x++ = 0.0;
      *x++ = e;
      *x++ = e;

      // third row
      x = S[2];
      x1 = x + R;
      *x++ = f;
      const double* F = x;
      *x++ = f;
      *x++ = f;
      *x++ = f;
      while (x < x1)
        *x++ = 0.0;

      unsigned int k = 0;
      const unsigned int kmax = R - 1;

      for (unsigned int i = 3; i < R; i += 2)
      {
        x = S[i];
        y = S[i + 1];
        k = (k + (kmax - 2)) % kmax;
        *x++ = d_center;
        *y++ = f;
        x1 = x + kmax;
        while (x < x1)
        {
          *x++ = E[k];
          *y++ = F[k];
          k = (k + 1) % kmax;
        }
      }

      if (this->IsDartSector())
      {
        // fix creased edge row
        x = S[1];
        x1 = x + R;
        *x++ = 0.5; // center vertex
        *x++ = 0.5; // crease edge vertex
        while (x < x1)
          *x++ = 0.0;
      }
    }

    return R;
  }

  if ( this->IsCreaseSector() || this->IsCornerSector() )
  {
    // The Catmull-Clark subdivision matrix is singular for a crease
    // vertex with 2 crease edges and a single face.  This case gets
    // special handling in all ON_SubD code.
    // S[4][4] = {{3./4, 1./8, 0, 1./8}, {1./2, 1./2, 0, 0}, {1./4, 1./4, 1./4, 1./4}, {1./2, 0, 0, 1./2}};
    // eigenvalues[4] = {1, 1./2, 1./4, 1./4};
    // eigenvectors[3][4] = {{1, 1, 1, 1}, {0, -1, 0, 1}, {0, 0, 1, 0}};
    // (eigenvalue 1/4 has algebraic multiplicity = 2 and geometric multiplicity = 1)

    if (N < 2 || R < 4)
      return ON_SUBD_RETURN_ERROR(0);

    const double w = this->SectorCoefficient();

    double* x;
    double* y;
    double* x1;

    if (this->IsCornerSector())
    {
      // first row (1, 0, ..., 0)
      x = S[0];
      x1 = x + R;
      *x++ =1.0;
      while (x < x1)
        *x++ = 0.0;
    }
    else
    {
      // first row (3/4, 1/8, 0, ..., 0, 1/8)
      x = S[0];
      *x++ = 0.75;
      *x++ = 0.125;
      x1 = x + R - 3;
      while (x < x1)
        *x++ = 0.0;
      *x = 0.125;
    }

    // second row (1/2, 1/2, 0, ..., 0)
    x = S[1];
    *x++ = 0.5;
    *x++ = 0.5;
    x1 = x + R - 2;
    while (x < x1)
      *x++ = 0.0;

    // third row (1/4, 1/4, 1/4, 1/4, 0, ..., 0)
    x = S[2];
    *x++ = 0.25;
    *x++ = 0.25;
    *x++ = 0.25;
    *x++ = 0.25;
    x1 = x + R-4;
    while (x < x1)
      *x++ = 0.0;

    // last row (1/2, 0, ..., 0, 1/2)
    x = S[R - 1];
    *x++ = 0.5;
    x1 = x + R - 2;
    while (x < x1)
      *x++ = 0.0;
    *x = 0.5;

    if (R > 4)
    {
      // penultimate row (1/4, 0, ..., 0, 1/4, 1/4, 1/4 )
      x = S[R - 2];
      *x++ = 0.25;
      x1 = x + R - 4;
      while (x < x1)
        *x++ = 0.0;
      *x++ = 0.25;
      *x++ = 0.25;
      *x = 0.25;

      // fourth row (3w/4, 1/16,1/16,3(1-w)/4,1/16,1/16, 0, ...., 0)
      x = S[3];
      *x++ = 0.75*w;
      *x++ = 0.0625;
      *x++ = 0.0625;
      *x++ = 0.75*(1.0 - w);
      *x++ = 0.0625;
      *x++ = 0.0625;
      x1 = x + R - 6;
      while (x < x1)
        *x++ = 0.0;

      if (R > 6)
      {
        unsigned int k = 0;
        const unsigned int kmax = R - 1;
        const double* F = S[2];
        const double* E = S[3];
        const double F0 = *F++;
        const double E0 = *E++;
        for (unsigned int i = 4; i < R - 2; i += 2)
        {
          x = S[i];
          y = S[i + 1];
          *x++ = F0;
          *y++ = E0;
          k = (k + (kmax - 2)) % kmax;
          x1 = x + kmax;
          while (x < x1)
          {
            *x++ = F[k];
            *y++ = E[k];
            k = (k + 1) % kmax;
          }
        }
      }
    }

    return R;
  }

  return ON_SUBD_RETURN_ERROR(0);

}

unsigned int ON_SubDSectorType::GetSubdivisionMatrix(
  double* S,
  size_t S_capacity
  ) const
{
  if ( S_capacity < 9 || nullptr == S )
    return ON_SUBD_RETURN_ERROR(0);

  const unsigned int R = PointRingCount();
  if (R < 3)
    return ON_SUBD_RETURN_ERROR(0);

  if ( S_capacity < R*R )
    return ON_SUBD_RETURN_ERROR(0);

  double** Srows = new(std::nothrow) double* [R];
  if ( nullptr == Srows)
    return ON_SUBD_RETURN_ERROR(0);
  Srows[0] = S;
  for (unsigned int i = 1; i < R; i++)
  {
    Srows[i] = Srows[i-1] + R;
  }

  const unsigned int rc = GetSubdivisionMatrix(Srows, R);
  
  delete[] Srows;

  return rc;
}

double ON_SubDSectorType::SubdominantEigenvalue() const
{
  const double rc_error = ON_UNSET_VALUE;
  const unsigned int R = PointRingCount();
  if (R < 3)
    return ON_SUBD_RETURN_ERROR(rc_error);

  const unsigned int F = FaceCount();
  if (F < 1)
    return ON_SUBD_RETURN_ERROR(rc_error);

  switch (VertexTag())
  {
  case ON_SubDVertexTag::Unset:
    break;

  case ON_SubDVertexTag::Smooth:
    if (1 == (R % 2))
    {
      // April 2019 Dale Lear - Catmull Clark Valence 2 Evaluation: Smooth
      // See comments in ON_SubDSectorType::GetSurfaceEvaluationCoefficients()
      // for more details on how this case is handled.
      //
      // R = 5 is the valence 2 case.
      // In this case the evaluation matrix is 5x5 and the eigenvalues are 
      // In this case the evaluation matrix is 5x5 and the eigenvalues are 
      // 1, 1/4, 1/4, -1/4, 1/8.
      // The multiplicity of 1/4 is two, but -1/4 is also a subdominant eigenvalue.
      // This function returns 1/4 when R = 5 and tag = Smooth.

      double cos_2pi_over_F, cos_pi_over_F, lambda;
      ON_SubDMatrix::EvaluateCosAndSin(2, F, &cos_2pi_over_F, &lambda);
      ON_SubDMatrix::EvaluateCosAndSin(1, F, &cos_pi_over_F, &lambda);
      lambda = (5.0 + cos_2pi_over_F + 3.0*cos_pi_over_F*sqrt(2.0*(1.0 + cos_2pi_over_F/9.0)))/16.0;
      return lambda;
    }
    break;

  case ON_SubDVertexTag::Dart:
    // April 2019 Dale Lear - Catmull Clark Valence 2 Evaluation: Dart
    // See comments in ON_SubDSectorType::GetSurfaceEvaluationCoefficients()
    // for more details on how this case is handled.
    //
    // R = 5 is the valence 2 case.
    // In this case the evaluation matrix is 5x5 and the eigenvalues are 
    // 1, 1/2, 1/4, sqrt(2)/8, -sqrt(2)/8.
    // All eigenvalues have multiplicity 1, including the subdominant 1/2.
    // This function returns 1/2 when R = 5 and tag = Dart.

    if (1 == (R % 2))
      return 0.5;
    break;


  case ON_SubDVertexTag::Corner:
  case ON_SubDVertexTag::Crease:
    if (0 == (R % 2))
      return 0.5;
    break;
  }

  return ON_SUBD_RETURN_ERROR(rc_error);
}


unsigned int ON_SubDSectorType::SubdominantEigenvalueMulitiplicity() const
{
  if (false == IsValid() )
    return 0;

  // Catmull-Clark quad subdivision special cases
  if (ON_SubDVertexTag::Crease == m_vertex_tag)
  {
    if (0 == m_sector_face_count)
    {
      // "wire" edges (no faces)
      // In this case the evaluation matrix is 3x3 and the eigenvalues are 
      // 1, 1/2, 1/4.
      // All eigenvalues have multiplicity 1, including the subdominant 1/2.
      return 1; // for the 1/2
    }
    if (1 == m_sector_face_count)
    {
      // single face 
      // In this case the evaluation matrix is 4x4 and the eigenvalues are 
      // 1, 1/2, 1/4, 1/4. 
      // The Jordan block for 1/4, 1/4 had a 1 on the super diagonal.
      return 1; // for the 1/2
    }
  }
  else if (2 == m_sector_face_count)
  {
    // valance 2 special cases
    if (ON_SubDVertexTag::Smooth == m_vertex_tag)
    {
      // April 2019 Dale Lear - Catmull Clark Valence 2 Evaluation: Smooth
      // See comments in ON_SubDSectorType::GetSurfaceEvaluationCoefficients()
      // for more details on how this case is handled.
      //
      // In this case the evaluation matrix is 5x5 and the eigenvalues are
      // 1, 1/4, 1/4, -1/4, 1/8.
      // The multiplicity of 1/4 is two, but -1/4 is also a subdominant eigenvalue.
      // For valence >= 3 the Smooth eigenvalues are 1, 1/4, 1/4, smaller values ...
      return 2; // for the 1/4, 1/4 pair
    }

    if (ON_SubDVertexTag::Dart == m_vertex_tag)
    {
      // April 2019 Dale Lear - Catmull Clark Valence 2 Evaluation: Dart
      // See comments in ON_SubDSectorType::GetSurfaceEvaluationCoefficients()
      // for more details on how this case is handled.
      //
      // In this case the evaluation matrix is 5x5 and the eigenvalues are 
      // 1, 1/2, 1/4, sqrt(2)/8, -sqrt(2)/8.
      // All eigenvalues have multiplicity 1, including the subdominant 1/2.
      return 1; // for the 1/2
    }

  }

  // For a Corner vertex with valence = 0 (wire edges), the matrix is 3x3 and the eigenvalues are 1, 1/2, 1/2.
  // For a Corner vertex with valence = 1 (single face), the matrix is 4x4 and the eigenvalues are 1, 1/2, 1/2, 1/4.
  // For a Smooth vertex with valence >= 3, the eigenvalues are 1, 1/4, 1/4, smaller values ...
  // For a Dart vertex with valence >= 3, the eigenvalues are 1, 1/2, 1/2, smaller values ...
  return 2;
}

double ON_SubDSectorType::GetSubdominantEigenvectors(
  double* E1,
  size_t E1_capacity,
  double* E2,
  size_t E2_capacity
) const
{
  const double rc_error = ON_UNSET_VALUE;
  const double lambda = SubdominantEigenvalue();
  if (!(lambda > 0.0 && lambda < 1.0))
    return ON_SUBD_RETURN_ERROR(rc_error);

  const unsigned int R = PointRingCount();
  if (R < 3)
    return ON_SUBD_RETURN_ERROR(rc_error);

  const unsigned int F = FaceCount();
  if (F < 1)
    return ON_SUBD_RETURN_ERROR(rc_error);

  if ( 0 == E1_capacity)
    E1 = nullptr;
  else if (E1_capacity < R || nullptr == E1)
  {
    return ON_SUBD_RETURN_ERROR(rc_error);
  }

  if ( 0 == E2_capacity)
    E2 = nullptr;
  else if (E2_capacity < R || nullptr == E2)
  {
    return ON_SUBD_RETURN_ERROR(rc_error);
  }

  if (nullptr == E1 || nullptr == E2)
  {
    // If one of LT0ev or E2 is null, then both must be null.
    if (nullptr != E1 || nullptr != E2)
    {
      return ON_SUBD_RETURN_ERROR(rc_error);
    }
  }

  double y, cos0, cos1, sin0, sin1;

  switch (VertexTag())
  {
  case ON_SubDVertexTag::Unset:
    break;

  case ON_SubDVertexTag::Smooth:
    if (1 == (R % 2))
    {
      if (nullptr != E1)
      {
        // cos0 = cos(2pi * 0/F)
        // sin0 = sin(2pi * 0/F)
        // cos1 = cos(2pi * 1/F)
        // sin1 = sin(2pi * 1/F)
        cos0 = 1.0;
        sin0 = 0.0;
        ON_SubDMatrix::EvaluateCosAndSin(2, F, &cos1, &sin1);
        //y = 0.5*(3.0 * sqrt((1.0 + cos1 / 9.0) / (1.0 + cos1)) - 1.0);
        y = (0.25 == lambda) ? -1.0 : (2.0*(4.0*lambda - 1.0) / (1.0 + cos1) - 1.0);
        E1[0] = 0.0;
        E2[0] = 0.0;
        E1[1] = sin0;
        E2[1] = cos0;
        unsigned int i = 2;
        for (;;)
        {
          E1[i] = y*(sin0 + sin1);
          E2[i] = y*(cos0 + cos1);
          i++;
          if (i==R)
            break;
          E1[i] = sin1;
          E2[i] = cos1;
          i++;
          cos0 = cos1;
          sin0 = sin1;
          ON_SubDMatrix::EvaluateCosAndSin(i, F, &cos1, &sin1);
          // E1[] and E2[] values are symmetric and we could stop halfway and copy
          // current loop debugged and tested Feb 10, 2015
        }
      }
      return lambda;
    }
    break;

  case ON_SubDVertexTag::Dart:
    if (1 == (R % 2))
    {
      if (nullptr != E1)
      {
        // cos0 = cos(2pi * 0/F)
        // sin0 = sin(2pi * 0/F)
        // cos1 = cos(2pi * 1/F)
        // sin1 = sin(2pi * 1/F)
        cos0 = 1.0;
        sin0 = 0.0;
        ON_SubDMatrix::EvaluateCosAndSin(2, F, &cos1, &sin1);
        E1[0] = 0.0;
        E2[0] = 0.0;
        E1[1] = sin0;
        E2[1] = cos0;
        unsigned int i = 2;
        for (;;)
        {
          E1[i] = sin0 + sin1;
          E2[i] = cos0 + cos1;
          i++;
          if (i==R)
            break;
          E1[i] = sin1;
          E2[i] = cos1;
          i++;
          cos0 = cos1;
          sin0 = sin1;
          ON_SubDMatrix::EvaluateCosAndSin(i, F, &cos1, &sin1);
          // E1[] and E2[] values are symmetric and we could stop halfway and copy
          // current loop debugged and tested Feb 10, 2015
        }
      }
      return lambda;
    }
    break;

  case ON_SubDVertexTag::Corner:
    if (0 == (R % 2))
    {
      const unsigned int sector_angle_index = CornerSectorAngleIndex();
      const unsigned int M = ON_SubDSectorType::MaximumCornerAngleIndex;
      //const unsigned int I = ((2*sector_angle_index <= M) ? sector_angle_index : (M-sector_angle_index));
      const unsigned int I = 2*((2*sector_angle_index <= M) ? sector_angle_index : (M-sector_angle_index));
      // F faces, F-1 interior smooth edges and 2 boundary edges
      // theta = (i/M*2pi)/F
      cos1 = 1.0; // = cos(0)
      sin1 = 0.0; // = sin(0)
      E1[0] = 0.0;
      E2[0] = 0.0;
      unsigned int i = 1;
      for (;;)
      {
        cos0 = cos1;
        sin0 = sin1;
        ON_SubDMatrix::EvaluateCosAndSin((i/2 + 1)*I,F*M,&cos1,&sin1);
        E1[i] = sin0;
        E2[i] = cos0;
        i++;
        E1[i] = sin0+sin1;
        E2[i] = cos0+cos1;
        i++;
        if (R - 1 == i)
        {
          E1[i] = sin1; // = sin(pi)
          E2[i] = cos1; // = cos(pi)
          break;
        }
      }
      return lambda;
    }
    break;

  case ON_SubDVertexTag::Crease:
    if (0 == (R % 2))
    {
      if (1 == F)
      {
        // one face and 2 boundary edges
        // E1 = eigenvector with eigenvalue = 1/2
        E1[0] =  0.0; // center point coefficients
        E1[1] =  1.0; // initial boundary edge point coefficient
        E1[2] =  0.0; // face point coefficient
        E1[3] = -1.0; // final boundary edge point coefficient


        // (0,0,1,0) = eigenvector with eigenvalue = 1/4.
        // E2 is not an eigenvector
        // S * E2 = (1/4, 1/4, 2/5, 1/4)
        E2[0] =  1.0; // center point coefficients
        E2[1] = -2.0; // boundary edge point coefficient
        E2[2] = -5.0; // face point coefficient
        E2[3] = -2.0; // boundary edge point coefficient
      }
      else
      {
        // F faces, F-1 interior smooth edges and 2 boundary edges
        // theta = pi/F
        cos1 = 1.0; // = cos(0)
        sin1 = 0.0; // = sin(0)
        E1[0] = 0.0;
        E2[0] = 0.0;
        unsigned int i = 1;
        for (;;)
        {
          cos0 = cos1;
          sin0 = sin1;
          ON_SubDMatrix::EvaluateCosAndSin(i/2 + 1,F,&cos1,&sin1);
          E1[i] = sin0;
          E2[i] = cos0;
          i++;
          E1[i] = sin0+sin1;
          E2[i] = cos0+cos1;
          i++;
          if (R - 1 == i)
          {
            E1[i] = sin1; // = sin(pi)
            E2[i] = cos1; // = cos(pi)
            break;
          }
        }
      }

      return lambda;
    }
    break;
  }

  return ON_SUBD_RETURN_ERROR(rc_error);
}

static double ON_SubDSectorType_LimitSurfaceNormalSign(
  unsigned int R,
  double sector_angle,
  const double* L1,
  const double* L2
  )
{
  // Evaluate a point ring is a counterclockwise circle in the x-y plane with center vertex at (0,0).

  const double delta_a = sector_angle / (R-1);
  ON_2dVector T[2] = { ON_2dVector::ZeroVector, ON_2dVector::ZeroVector };
  double a = 0.0;
  for (unsigned int i = 1; i < R; i++, a += delta_a)
  {
    double ring_x = cos(a);
    double ring_y = sin(a);
    T[0].x += L1[i] * ring_x;
    T[0].y += L1[i] * ring_y;
    T[1].x += L2[i] * ring_x;
    T[1].y += L2[i] * ring_y;
  }
  T[0].Unitize();
  T[1].Unitize();
  // z-component of the cross product should be positive.
  double z = T[0].x * T[1].y - T[0].y * T[1].x;
  return z;
}

double ON_SubDSectorType::SurfaceNormalSign() const
{
  const double rc_error = ON_UNSET_VALUE;
  if (false == IsValid())
    return ON_SUBD_RETURN_ERROR(rc_error);

  const unsigned int R = PointRingCount();
  const ON_SubDVertexTag vertex_tag = VertexTag();

  ON_SimpleArray<double> buffer;
  double* LP = buffer.Reserve(3*R);
  if (nullptr == LP)
    return ON_SUBD_RETURN_ERROR(rc_error);
  double* L1 = LP + R;
  double* L2 = L1 + R;

  if (R != GetSurfaceEvaluationCoefficients(LP, R, L1, R, L2, R))
    return ON_SUBD_RETURN_ERROR(rc_error);

  double sector_angle;

  switch (vertex_tag)
  {
  case ON_SubDVertexTag::Smooth:
  case ON_SubDVertexTag::Dart:
    sector_angle = 2.0*ON_PI;
    break;
  case ON_SubDVertexTag::Crease:
    sector_angle = 0.5*ON_PI;
    break;
  case ON_SubDVertexTag::Corner:
    sector_angle = CornerSectorAngleRadians();
    break;
  default:
    return ON_SUBD_RETURN_ERROR(rc_error);
    break;
  }
  
  double z = ON_SubDSectorType_LimitSurfaceNormalSign(R,sector_angle,L1,L2);
  return z;
}

bool ON_SubDSectorType::SurfaceEvaluationCoefficientsAvailable() const
{
  if (IsValid())
  {
    // Available as of March 23, 2015
    //if (ON_SubDVertexTag::Dart == m_vertex_tag && FaceCount() > 5)
    //{
    //  // temporary limit
    //  return false;
    //}
    return true;
  }
  return false;
}



unsigned int ON_SubDSectorType::GetSurfaceEvaluationCoefficients(
  double* LP,
  size_t LP_capacity,
  double* L1,
  size_t L1_capacity,
  double* L2,
  size_t L2_capacity
  ) const
{
  const double lambda = SubdominantEigenvalue();
  if (!(lambda > 0.0 && lambda < 1.0))
    return ON_SUBD_RETURN_ERROR(0);

  
  const unsigned int R = PointRingCount();
  if (R < 3)
    return ON_SUBD_RETURN_ERROR(0);

  const unsigned int F = FaceCount();
  if (F < 1)
    return ON_SUBD_RETURN_ERROR(0);
  const double dF = F;

  if ( 0 == LP_capacity)
    LP = nullptr;
  else if (LP_capacity < R || nullptr == LP)
  {
    return ON_SUBD_RETURN_ERROR(0);
  }

  if ( 0 == L1_capacity)
    L1 = nullptr;
  else if (L1_capacity < R || nullptr == L1)
  {
    return ON_SUBD_RETURN_ERROR(0);
  }

  if ( 0 == L2_capacity)
    L2 = nullptr;
  else if (L2_capacity < R || nullptr == L2)
  {
    return ON_SUBD_RETURN_ERROR(0);
  }

  if (nullptr == L1 || nullptr == L2)
  {
    // If one of L1 or L2 is null, then both must be null.
    if (nullptr != L1 || nullptr != L2)
    {
      return ON_SUBD_RETURN_ERROR(0);
    }
  }

  double p, q, y, z, cos0, cos1, sin0, sin1;
  bool b180degreeCorner = false;

  switch (VertexTag())
  {
  case ON_SubDVertexTag::Unset:
    break;

  case ON_SubDVertexTag::Smooth:
    if (R >= 5 && 1 == (R % 2))
    {
      if (nullptr != LP)
      {
        // April 2019 Dale Lear - Catmull Clark Valence 2 Evaluation: Smooth
        //
        // General case code works for R = 5 case: LP[5] = {2/7, 2/7, 1/14, 2/7, 1/14};
        LP[0] = dF / (5.0 + dF); // center point coefficient
        y = dF * (dF + 5.0);
        p = 4.0 / y; // edge point coefficient
        q = 1.0 / y; // face point coefficient
        for (unsigned int i = 1; i < R; i++)
        {
          LP[i] = p;
          i++;
          LP[i] = q;
        }
      }

      if (nullptr != L1)
      {
        if (5 == R)
        {
          // April 2019 Dale Lear - Catmull Clark Valence 2 Evaluation: Smooth
          //
          // Evaluation matrix has eigenvalues 1, 1/4, 1/4, -1/4, 1/8,
          // so we have a well defined limit point and 3 subdominant eigenvalues. 
          // The 1 eigenspace is 1 dimensional and spanned by (1,1,1,1,1).
          // The 1/4 eigenspace is 2 dimensional and spanned by (0,1,0,-1,0) and (0,0,1,0,-1).
          // The -1/4 eigenspace is 1 dimensional and spanned by (2,-1,0,-1,0).
          // The 1/8 is 1 dimensional and spanned by (1,1,-6,1,-6).
          // The general case code below will divide by zero when y is evaluated because cos1 = -1.
          // Turns out there is 1 well defined tangent vector (Q1-Q0) (quad points)

          // This is a "pseudo" limit tangent
          L1[0] = 0.0;
          L1[1] = 1.0;
          L1[2] = 0.0;
          L1[3] = -1.0;
          L1[4] = 0.0;

          // This is a bonafide limit tangent
          L2[0] = 0.0;
          L2[1] = 0.0;
          L2[2] = 1.0;
          L2[3] = 0.0;
          L2[4] = -1.0;
        }
        else
        {
          // cos0 = cos(2pi * 0/F)
          // sin0 = sin(2pi * 0/F)
          // cos1 = cos(2pi * 1/F)
          // sin1 = sin(2pi * 1/F)
          cos0 = 1.0;
          sin0 = 0.0;
          ON_SubDMatrix::EvaluateCosAndSin(2, F, &cos1, &sin1);
          y = 2.0* (lambda - 0.125*(3.0 + cos1)) / (1.0 + cos1);
          L1[0] = 0.0;
          L1[1] = cos0;
          L2[0] = 0.0;
          L2[1] = sin0;
          unsigned int i = 2;
          for (;;)
          {
            L1[i] = y * (cos0 + cos1);
            L2[i] = y * (sin0 + sin1);
            i++;
            if (i == R)
              break;
            L1[i] = cos1;
            L2[i] = sin1;
            i++;
            cos0 = cos1;
            sin0 = sin1;
            ON_SubDMatrix::EvaluateCosAndSin(i, F, &cos1, &sin1);
            // E0[] and E1[] values are symmetric and we could stop halfway and copy
            // current loop debugged and tested Feb 10, 2015
          }
        }
      }
      return R;
    }
    break;

  case ON_SubDVertexTag::Dart:
    if (1 == (R % 2))
    {
      ON_Matrix Sbuffer;
      const double*const* S = nullptr;
      double* E1 = nullptr;
      double* E2 = nullptr;
      if (F > 5)
      {
        if (false == Sbuffer.Create(R+2,R))
          return ON_SUBD_RETURN_ERROR(0);
        if (R != ON_SubDSectorType::GetSubdivisionMatrix(Sbuffer.m, R))
          return ON_SUBD_RETURN_ERROR(0);
        S = Sbuffer.m;
        E1 = Sbuffer.m[R];
        E2 = Sbuffer.m[R+1];
      }
      const double* termination_tolerances = nullptr;
      double* eigenvectors[2] = { E1, E2 };
      double eigenprecision[2] = { 0 };
      double eigenpivots[3] = { 0 };

      if (nullptr != LP)
      {
        switch (F)
        {
        case 2:
          // April 2019 Dale Lear - Catmull Clark Valence 2 Evaluation: Dart
          //
          // Evaluation matrix is 5x5 with has eigenvalues 1, 1/2, 1/4, sqrt(2)/8, - sqrt(2)/8.
          LP[0] = 8.0 / 31.0;
          LP[1] = 10.0 / 31.0;
          LP[2] = 3.0 / 62.0;
          LP[3] = 10.0 / 31.0;
          LP[4] = 3.0 / 62.0;
          break;

        case 3:
          LP[0] = 243/19.0;
          LP[1] = 130/19.0;
          LP[2] = 1.0;
          LP[3] = 120/19.0;
          LP[4] = 29/19.0;
          //LP[5] = 120/19.0;
          //LP[6] = 1.0;
          break;
        case 4:
          LP[0] = 752/29.0;
          LP[1] = 210/29.0;
          LP[2] = 1.0;
          LP[3] = 160/29.0;
          LP[4] = 44/29.0;
          LP[5] = 180/29.0; 
          //LP[6] = 44/29.0;
          //LP[7] = 160/29.0;
          //LP[8] = 1.0;
          break;
        case 5:
          LP[0] = 43.222764462468341719; 
          LP[1] = 7.4578211569974673376; 
          LP[2] = 1.0;
          LP[3] = 5.0843576860050653249; 
          LP[4] = 1.4771459186191773181; 
          LP[5] = 5.7257510234301278178;
          LP[6] = 1.5305953634045991926;
          //LP[7] = 5.7257510234301278178; 
          //LP[8] = 1.4771459186191773181;
          //LP[9] = 5.0843576860050653249;
          //LP[10] = 1.0000000000000000000;
          break;
        default:
          {
            // TODO
            // Finish general case formula for dominant eigenvector of Transpose(S)
            // Until I derive the formula, I can get the dominant eigenvector as the kernel of the matrix (S - I).
            // This calculation has plenty of precision, but it's a less elegant way to get the solution.
            if (nullptr == S)
              return ON_SUBD_RETURN_ERROR(0);
            const double lambda_local = 1.0;
            const unsigned int lambda_multiplicity = 1;
            if (lambda_multiplicity != ON_GetEigenvectors(R, S, true, lambda_local, lambda_multiplicity, termination_tolerances, eigenvectors, eigenprecision, eigenpivots))
              return ON_SUBD_RETURN_ERROR(0);
            if (E1[0] < 0.0)
            {
              for ( unsigned int i = 0; i < R; i++ )
                E1[i] = -E1[i];
            }
            for (unsigned int i = 0; i < R; i++)
            {
              if (E1[i] < 0.0)
                return ON_SUBD_RETURN_ERROR(0);
            }
            LP[0] = E1[0];
            LP[1] = E1[1];
            unsigned int i0 = 2;
            unsigned int i1 = R-1;
            while (i0 <= i1)
            {
              LP[i0] = (E1[i0] == E1[i1]) ? E1[i0] : 0.5*(E1[i0] + E1[i1]);
              i0++;
              i1--;
            }
          }
          break;
        }

        if (F >= 3)
        {
          // The code below works for all F >= 3.
          const double* q0 = &LP[2];
          double* q1 = &LP[R - 1];
          while (q0 < q1)
            *q1-- = *q0++;
          double LPsum = 0.0;
          for (unsigned int i = 0; i < R; i++)
            LPsum += LP[i];
          for (unsigned int i = 0; i < R; i++)
            LP[i] /= LPsum;
        }
      }

      if (nullptr != L1)
      {
        switch (F)
        {
        case 2:
          // April 2019 Dale Lear - Catmull Clark Valence 2 Evaluation: Dart
          //
          // Evaluation matrix is 5x5 with has eigenvalues 1, 1/2, 1/4, sqrt(2)/8, - sqrt(2)/8.
          // The multiplicity of the subdominant eigen value is 1/2 and there is a single well defined
          // tangent in the limit surface. The other is a "fake" tangent that is close enough.

          // This is pseudo tangent associated with the eigenvalue 1/4
          // (1/4)^n goes to zero much faster than (1/2)^n, but ...
          // If the 5 points were translated so the limit point was zero 
          // and then a rotation about the origin were applied so bonafide limit tangent
          // was parallel to the x-axis (L2*(C,P0,Q0,P1,P1) = 0), then, as n goes to infinity,
          // Q0 - Q1 would be the farthest point from the x-axis.
          // the 5 
          L1[0] = 0.0;
          L1[1] = 0.0;
          L1[2] = -1.0;
          L1[3] = 0.0;
          L1[4] = 1.0;

          // This is a bonafide limit tangent associated with the eigenvalue 1/2.
          // I
          L2[0] = 4.0; // 2^2
          L2[1] = 6.0; 
          L2[2] = -1.0; 
          L2[3] = -8.0;
          L2[4] = -1.0;
          break;

        case 3:
          L1[0] = -9/4.0; // -L2[0]/4
          L1[1] = -3.0;
          L1[2] = 1/2.0;
          L1[3] = 3.0; 
          L1[4] = 3/4.0;
          L1[5] = 1;
          L1[6] = 0;

          L2[0] = 9.0; // 3^2
          L2[1] = 12.0; 
          L2[2] =  -3; 
          L2[3] = -16;  // -16  // -3, -16 = L2[3] = -16, -3
          L2[4] =  -3;  //  -3
          L2[5] = 0; 
          L2[6] = 1;
          break;

        case 4:
          L1[0] = -4.0;  // -L2[0]/4
          L1[1] = -7.0; 
          L1[2] = 1/2.0; 
          L1[3] = 3.0; 
          L1[4] = 3/2.0; 
          L1[5] = 4.0; 
          L1[6] = 1.0; 
          L1[7] = 1; 
          L1[8] = 0;

          L2[0] = 16.0; // 4^2
          L2[1] = 28.0;
          L2[2] =  -3;
          L2[3] = -16;
          L2[4] = -7.0;   // -3, -16, L2[4], -16, -3
          L2[5] = -16; 
          L2[6] =  -3;
          L2[7] = 0;
          L2[8] = 1;
          break;

        case 5:
          L1[0] = -6.25; // -L2[0]/4
          L1[1] = -14.208203932499369089;
          L1[2] = 0.50000000000000000000;
          L1[3] = 3.0000000000000000000;
          L1[4] = 1.9635254915624211362;
          L1[5] = 5.8541019662496845446;
          L1[6] = 2.3680339887498948482; 
          L1[7] = 4.6180339887498948482;
          L1[8] = 1.1545084971874737121;
          L1[9]  = 1;
          L1[10] = 0;

          L2[0] = 25.0; // 5^2
          L2[1] = 56.832815729997476357;
          L2[2] =  -3;
          L2[3] = -16;
          L2[4] = -9.4721359549995793928;
          L2[5] = -25.888543819998317571; // -3, -16, ..., L2[5], ..., -16, -3
          L2[6] = -9.4721359549995793928;
          L2[7] = -16; // -16 
          L2[8] =  -3; //  -3
          L2[9]  = 0;
          L2[10] = 1;
          break;

        default:
          {
            // TODO
            // Finish general case formula for subdominant eigenvectors of Transpose(S)
            // Until I derive the formula, I can get the subdominant eigenvectors as the kernel of the matrix (S - 1/2*I).
            // This calculation has plenty of precision, but it's a less elegant way to get the solution.
            if (nullptr == S)
              return ON_SUBD_RETURN_ERROR(0);
            const double lambda_local = SubdominantEigenvalue();
            if (!(lambda_local > 0.0 && lambda_local < 1.0))
              return ON_SUBD_RETURN_ERROR(0);
            const unsigned int lambda_multiplicity = 2;
            if (lambda_multiplicity != ON_GetEigenvectors(R, S, true, lambda_local, lambda_multiplicity, termination_tolerances, eigenvectors, eigenprecision, eigenpivots))
              return ON_SUBD_RETURN_ERROR(0);

            const double E[2][2] = { { E1[R - 2], E2[R - 2] }, { E1[R - 1], E2[R - 1] } };

            const double det = E[0][0] * E[1][1] - E[0][1] * E[1][0];
            if (!(0.0 != det))
              return 0;

            const double EtoL[2][2] = {
              { E[1][1] / det, (0.0 == E[0][1]) ? 0.0 : (-E[0][1] / det) },
              { (0.0 == E[1][0]) ? 0.0 : (-E[1][0] / det), E[0][0] / det } };

            for (unsigned int i = 0; i < R; i++)
            {
              L1[i] = E1[i] * EtoL[0][0] + E2[i] * EtoL[1][0];
              L2[i] = E1[i] * EtoL[0][1] + E2[i] * EtoL[1][1];
            }

            const double int_tol = 1e-12;
            double x;
            for (unsigned int i = 0; i < R; i++)
            {
              x = floor(L1[i]+0.49);
              if (fabs(x - L1[i]) <= int_tol)
                L1[i] = x;
              x = floor(L2[i]+0.49);
              if (fabs(x - L2[i]) <= int_tol)
                L2[i] = x;
            }

            L1[0]     = -0.25*F*F;
            L1[R - 2] = 1.0;
            L1[R - 1] = 0.0;

            L2[0]   = F*F;
            L2[2]   = -3.0;
            L2[3]   = -16.0;
            L2[R-4] = -16.0;
            L2[R-3] =  -3.0;
            L2[R-2] =   0.0;
            L2[R-1] =   1.0;

            // L2[2, ..., R-1] is symmetric about L2[2+R/2]
            unsigned int i0 = 4;
            unsigned int i1 = R - 5;
            while (i0 < i1)
            {
              if (L2[i0] != L2[i1])
              {
                x = 0.5*(L2[i0] + L2[i1]);
                L2[i0] = x;
                L2[i1] = x;
              }
              i0++;
              i1--;
            }
          }
          break;
        }
      }
      return R;
    }
    break;


  case ON_SubDVertexTag::Corner:
    if (0 == (R % 2))
    {
      const unsigned int angle_index = CornerSectorAngleIndex();
      if ( 36 == angle_index && F > 1)
        b180degreeCorner = true; // use crease calculation
      else
      {
        // the corner angle alpha is not equal to pi (180 degrees)
        // so limit tangents will not be parallel
        // Lpev[]
        LP[0] = 1.0; // center point coefficient
        for (unsigned int i = 1; i < R; i++)
          LP[i++] = 0.0; // all face and edge coefficients = 0

        L1[0] = -1.0; // center point coefficient
        L1[1] = 1.0; // initial boundary edge point coefficient
        L1[R - 1] = 0.0; // final boundary edge point coefficient

        // The sign of s is selected to keep the normal pointing "up".
        double s = (2 * angle_index <= ON_SubDSectorType::MaximumCornerAngleIndex) ? 1.0 : -1.0;
        L2[0] = -s; // center point coefficient
        L2[1] = 0.0; // initial boundary edge point coefficient
        L2[R - 1] = s; // final boundary edge point coefficient
        for (unsigned int i = 2; i + 1 < R; i++)
        {
          L1[i] = 0.0; // all face and interior edge coefficients = 0
          L2[i] = 0.0; // all face and interior edge coefficients = 0
        }

        if (36 == angle_index && 1 == F && 4 == R)
        {
          // This case has no good solution.
          L2[0] = -1.0;
          L2[1] = 0.0;
          L2[2] = 1.0;
          L2[3] = 0.0;
        }

        // TODO deal with 180 degree "corner case".  
        // L0 and L1 are the same as above. L2 will be similar to the crease case
        return R;
      }
    }
    if ( false == b180degreeCorner)
      break;

  case ON_SubDVertexTag::Crease:
    // NOTE: In the case when there are 2 crease edes and a single face,
    // The Catmull-Clark subdivision matrix is singular.
    if (0 == (R % 2))
    {
      // Lpev[]
      if (b180degreeCorner)
      {
        LP[0] = 1.0; // center point coefficient
        for (unsigned int i = 1; i < R; i++)
          LP[i++] = 0.0; // all face and edge coefficients = 0
      }
      else
      {
        LP[0] = 2.0 / 3.0; // center point coefficient
        LP[1] = LP[R - 1] = 1.0 / 6.0;  // boundary edge point coefficients
        for (unsigned int i = 2; i + 1 < R; i++)
          LP[i++] = 0.0; // all face and interior edge coefficients = 0
      }

      // Using L1[] computes the tangent to the crease curve. This
      // curve is a uniform cubic spline with control points
      // (..., final crease edge point, center point, initial crease edge point, ...)
      L1[  0] =  0.0; // center point coefficient
      L1[  1] =  1.0; // initial boundary edge point coefficient
      L1[R-1] = -1.0; // final boundary edge point coefficient
      for (unsigned int i = 2; i+1 < R; i++)
        L1[i] = 0.0; // all face and interior edge coefficients = 0

      // Using L2[] computes a tangent that points from the limit point
      // into the subdivision surface.
      if (1 == F)
      {
        // This is the special where IsCatmullClarkCreaseOneFaceCase() returns true.
        // Catmull-Clark subdivision,
        // center vertex is a crease vertex,
        // one face and two crease edges.
        L2[0] = -2.0; // center point coefficients
        L2[1] =  1.0; // boundary edge point coefficient
        L2[2] =  0.0; // face point coefficient
        L2[3] =  1.0; // boundary edge point coefficient
      }
      else
      {
        // F faces, F-1 interior smooth edges and 2 boundary edges
        // theta = pi/F
        cos0 = 1.0; // cos(0)
        sin0 = 0.0; // sin(0)
        ON_SubDMatrix::EvaluateCosAndSin(1,F,&cos1,&sin1); // cos1 = cos(pi/F), sin1 = sin(pi/F)
        z = (1.0 + cos1) / sin1;
        L2[0] = -sin1;  // center point coefficients
        L2[1] = -0.25*z*(1.0 + 2.0*cos1); // initial boundary edge point coefficient
        L2[2] = 0.25*(sin0 + sin1); // first interior face point coefficient
        L2[R-1] = L2[1];            // final boundary edge point coefficient
        unsigned int i = 3;
        for (;;)
        {
          cos0 = cos1;
          sin0 = sin1;
          ON_SubDMatrix::EvaluateCosAndSin(i/2 + 1, F, &cos1, &sin1);
          L2[i] = sin0; // interior edge point coefficient
          i++;
          L2[i] = 0.25*(sin0 + sin1); // interior face point coefficient
          i++;
          if ( i >= R-1 )
            break;
        }
      }

      return R;
    }
    break;
  }

  return ON_SUBD_RETURN_ERROR(0);
}

bool ON_SubDMatrix::IsValid() const
{
  return (m_sector_type.IsValid() && nullptr != m_S && m_R == m_sector_type.PointRingCount());
}

bool ON_SubDMatrix::IsValidPointRing(
  const double* point_ring,
  size_t point_ring_count,
  size_t point_ring_stride
  ) const
{
  return ( point_ring_count >= 4 && point_ring_stride >= 3 && nullptr != point_ring && m_R == point_ring_count);
}

bool ON_SubDMatrix::EvaluateSubdivisionPoint(
  unsigned int element_index,
  const double* point_ring,
  size_t point_ring_count,
  size_t point_ring_stride,
  double subd_point[3]
  ) const
{
  if ( nullptr == m_S || element_index >= m_R )
    return ON_SUBD_RETURN_ERROR(false);
  if (false == IsValidPointRing(point_ring,point_ring_count,point_ring_stride))
    return ON_SUBD_RETURN_ERROR(false);
 
  subd_point[0] = 0.0;
  subd_point[1] = 0.0;
  subd_point[2] = 0.0;
  double c;
  const double* s = m_S[element_index];
  const double* s1 = s + m_R;
  while (s < s1)
  {
    c = *s++;
    subd_point[0] += c*point_ring[0];
    subd_point[1] += c*point_ring[1];
    subd_point[2] += c*point_ring[2];
    point_ring += point_ring_stride;
  }

  return true;
}

bool ON_SubDMatrix::EvaluateSurfacePoint(
  const double* point_ring,
  size_t point_ring_count,
  size_t point_ring_stride,
  bool bUndefinedNormalIsPossible,
  ON_SubDSectorSurfacePoint& limit_point
  ) const
{
  limit_point.m_next_sector_limit_point = nullptr;
  limit_point.m_sector_face = nullptr;
  return EvaluateSurfacePoint(
    point_ring,
    point_ring_count,
    point_ring_stride,
    bUndefinedNormalIsPossible,
    limit_point.m_limitP,
    limit_point.m_limitT1,
    limit_point.m_limitT2,
    limit_point.m_limitN
    );
}

static bool Internal_GetAlterateTangent(
  const ON_SubDMatrix& subd_matrix,
  unsigned int Ldex,
  size_t point_ring_count,
  size_t point_ring_stride,
  const double* point_ring,
  const double L[3][3],
  double* alternate_tangent
)
{
  if (point_ring_count < 4 || point_ring_stride < 3 || nullptr == point_ring)
    return false;

  if (2 == Ldex)
  {
    if ( 4 == subd_matrix.m_R && ON_SubDVertexTag::Crease == subd_matrix.m_sector_type.VertexTag() )
    {
      // valence 2 crease case when crease edges are collinear
      // F = face point, C = crease vertex point.
      // Default tangents:
      //   L[1] = ON_3dPoint(point_ring +  point_ring_stride) - ON_3dPoint(point_ring + 3 * point_ring_stride);
      const ON_3dPoint C(point_ring);
      const ON_3dPoint Q(point_ring + 2 * point_ring_stride);
      ON_3dVector V(Q - C);
      if (V.IsNotZero())
      {
        alternate_tangent[0] = V.x;
        alternate_tangent[1] = V.y;
        alternate_tangent[2] = V.z;
        return true;
      }
    }
  }

  return false;
}

static bool Internal_GetAlterateNormal(
  const ON_SubDMatrix& subd_matrix,
  size_t point_ring_count,
  size_t point_ring_stride,
  const double* point_ring,
  double L[3][3],
  bool bHaveAlternateL[3],
  double alternate_normal[3]
)
{
  if (point_ring_count < 4 || point_ring_stride < 3 || nullptr == point_ring)
    return false;

  if ( 4 == subd_matrix.m_R && ON_SubDVertexTag::Crease == subd_matrix.m_sector_type.VertexTag() )
  {
    // valence 2 crease case when crease edges are collinear
    // F = face point, C = crease vertex point.
    ON_3dVector N(ON_3dVector::ZeroVector);
    if (false == bHaveAlternateL[2])
    {
      bHaveAlternateL[2] = Internal_GetAlterateTangent(subd_matrix, 2, point_ring_count, point_ring_stride, point_ring, L, L[2]);
      if (bHaveAlternateL[2])
      {
        ON_3dVector T1(L[1]);
        ON_3dVector T2(L[2]);
        N = ON_CrossProduct(T1, T2).UnitVector();
      }
    }
    if (N.IsZero())
    {
      N = ON_CrossProduct(L[1], L[2]).UnitVector();
      if (N.IsZero())
      {
        const ON_3dPoint C(point_ring);
        const ON_3dPoint P0(point_ring + 1 * point_ring_stride); // end of crease leaving C
        const ON_3dPoint Q(point_ring + 2 * point_ring_stride);
        const ON_3dPoint P1(point_ring + 1 * point_ring_stride); // end of crease entering C
        const ON_3dVector A = (P0 - P1).UnitVector();
        const ON_3dVector B = (Q - C).UnitVector();
        N = ON_CrossProduct(A, B).UnitVector();
      }
    }
    if (N.IsNotZero())
    {
      alternate_normal[0] = N.x;
      alternate_normal[1] = N.y;
      alternate_normal[2] = N.z;
      return true;
    }
  }

  return false;
}

bool ON_SubDMatrix::EvaluateSurfacePoint(
  const double* point_ring,
  size_t point_ring_count,
  size_t point_ring_stride,
  bool bUndefinedNormalIsPossible,
  double limit_point[3],
  double limit_tangent1[3],
  double limit_tangent2[3],
  double limit_normal[3]
  ) const
{
  if (nullptr != limit_point)
  {
    limit_point[0] = ON_DBL_QNAN;
    limit_point[1] = ON_DBL_QNAN;
    limit_point[2] = ON_DBL_QNAN;
  }

  if (nullptr != limit_normal)
  {
    limit_normal[0] = ON_DBL_QNAN;
    limit_normal[1] = ON_DBL_QNAN;
    limit_normal[2] = ON_DBL_QNAN;
  }

  if (nullptr != limit_tangent1)
  {
    limit_tangent1[0] = ON_DBL_QNAN;
    limit_tangent1[1] = ON_DBL_QNAN;
    limit_tangent1[2] = ON_DBL_QNAN;
  }

  if (nullptr != limit_tangent2)
  {
    limit_tangent2[0] = ON_DBL_QNAN;
    limit_tangent2[1] = ON_DBL_QNAN;
    limit_tangent2[2] = ON_DBL_QNAN;
  }
  
  if (nullptr == m_LP || nullptr == m_L1 || nullptr == m_L2 )
    return ON_SUBD_RETURN_ERROR(false);
  
  if (false == IsValidPointRing(point_ring,point_ring_count,point_ring_stride))
    return ON_SUBD_RETURN_ERROR(false);

  double x, y, z, c, L[3][3] = { {0.0,0.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0} };
  const double* s[3] = { m_LP, m_L1, m_L2 };
  const double* s1 = s[0]+m_R;
  const double* P = point_ring;
  while (s[0] < s1)
  {
    x = P[0];
    y = P[1];
    z = P[2];
    P += point_ring_stride;

    c = *s[0]++;
    L[0][0] += c*x;
    L[0][1] += c*y;
    L[0][2] += c*z;

    c = *s[1]++;
    L[1][0] += c*x;
    L[1][1] += c*y;
    L[1][2] += c*z;

    c = *s[2]++;
    L[2][0] += c*x;
    L[2][1] += c*y;
    L[2][2] += c*z;
  }

  if (nullptr != limit_point)
  {
    limit_point[0] = L[0][0];
    limit_point[1] = L[0][1];
    limit_point[2] = L[0][2];
  }

  if (nullptr == limit_tangent1 && nullptr == limit_tangent2 && nullptr == limit_normal)
    return true;

  bool bHaveAlternateL[3] = {};
  for (unsigned int Ldex = 1; Ldex < 3; ++Ldex)
  {
    if (0.0 == L[Ldex][0] && 0.0 == L[Ldex][1] && 0.0 == L[Ldex][2])
    {
      Internal_GetAlterateTangent(*this, Ldex, point_ring_count, point_ring_stride, point_ring, L, L[Ldex]);
      bHaveAlternateL[Ldex] = true;
    }
  }

  ON_3dVector T1(L[1]);
  T1.Unitize();  

  ON_3dVector T2(L[2]);
  T2.Unitize();  

  ON_3dVector N = ON_CrossProduct(T1, T2);
  N.Unitize();
  if (N.IsZero())
  {
    Internal_GetAlterateNormal(
      *this,
      point_ring_count,
      point_ring_stride,
      point_ring,
      L,
      bHaveAlternateL,
      &N.x
    );
  }

  if (nullptr != limit_tangent1)
  {
    limit_tangent1[0] = T1.x;
    limit_tangent1[1] = T1.y;
    limit_tangent1[2] = T1.z;
    if (0.0 == limit_tangent1[0] && 0.0 == limit_tangent1[1] && 0.0 == limit_tangent1[2])
    {
      if (false == bUndefinedNormalIsPossible)
      {
        ON_ERROR("limit_tangent1[0] = zero vector");
        bUndefinedNormalIsPossible = true; // one error is sufficient
      }
    }
  }

  if (nullptr != limit_tangent2)
  {
    limit_tangent2[0] = T2.x;
    limit_tangent2[1] = T2.y;
    limit_tangent2[2] = T2.z;
    if (0.0 == limit_tangent2[0] && 0.0 == limit_tangent2[1] && 0.0 == limit_tangent2[2])
    {
      if ( false == bUndefinedNormalIsPossible )
      {
        ON_ERROR("limit_tangent2[0] = zero vector");
        bUndefinedNormalIsPossible = true; // one error is sufficient
      }
    }
  }

  if (nullptr != limit_normal)
  {
    limit_normal[0] = N.x;
    limit_normal[1] = N.y;
    limit_normal[2] = N.z;
    if (0.0 == limit_normal[0] && 0.0 == limit_normal[1] && 0.0 == limit_normal[2])
    {
      if ( false == bUndefinedNormalIsPossible )
      {
        ON_ERROR("limit_normal[0] = zero vector");
      }
    }
  }

  return true;
}


class ON_SubDMatrixHashElement
{
public:
  ON_SubDMatrix m_sm;
  class ON_SubDMatrixHashElement* m_next = nullptr;
};

static ON_SubDMatrixHashElement* FindMatrixHashElement(
  const ON_SubDSectorType& sector_type,
  ON_SubDMatrixHashElement* element_list
  )
{
  for (/*empty init*/; nullptr != element_list; element_list = element_list->m_next)
  {
    if ( 0 == ON_SubDSectorType::Compare(&sector_type,&element_list->m_sm.m_sector_type) )
      return element_list;
  }
  return nullptr;
}

static int CompareMatrixHashElement(
  const ON_SubDMatrixHashElement* a,
  const ON_SubDMatrixHashElement* b
  )
{
  if ( a == b )
    return 0;

  // put nulls at end of list
  if (nullptr == a)
    return 1;
  if (nullptr == b)
    return -1;

  if (0 == a->m_sm.m_R || 0 == b->m_sm.m_R)
  {
    // at least one matrix is not valid - put invalid matrices at the end
    if ( a->m_sm.m_R > 0 )
      return -1;
    if ( b->m_sm.m_R > 0 )
      return 1;
  }

  return ON_SubDSectorType::Compare(&a->m_sm.m_sector_type,&b->m_sm.m_sector_type);
}

const ON_SubDMatrix& ON_SubDMatrix::FromCache(
  ON_SubDSectorType sector_type
  )
{
  // The ON_SubDMatrix cache is a global resource for the entire application.
  // This is a thread safe function that manages the ON_SubDMatrix cache.
  static ON_SleepLock lock;

  // The sector_type.Hash() is used to find elements in the cache.
  static ON_SubDMatrixHashElement* hash_table[256] = { 0 };

  const unsigned int hash = sector_type.SectorTypeHash();
  if (0 == hash)
    return ON_SUBD_RETURN_ERROR(ON_SubDMatrix::Empty); 

  const unsigned int hash_capacity = (unsigned int)sizeof(hash_table)/sizeof(hash_table[0]);
  const unsigned int hash_index = hash % hash_capacity;
  ON_SubDMatrixHashElement* hash_element = FindMatrixHashElement(sector_type,hash_table[hash_index]);
  if (nullptr != hash_element)
    return hash_element->m_sm;

  if ( false == sector_type.IsValid())
    return ON_SUBD_RETURN_ERROR(ON_SubDMatrix::Empty);

  // We need to add this case to the cache.
  
  // Lock the cache
  bool bReturnLock = lock.GetLock(0,30*ON_SleepLock::OneSecond);
  if (false == bReturnLock)
    bReturnLock = lock.GetLock(0, ON_SleepLock::OneSecond);

  // see if another thread made the sector matrix while we waited
  hash_element = FindMatrixHashElement(sector_type,hash_table[hash_index]);
  if (nullptr == hash_element)
  {
    // These matrices are created one time and then used many times.
    // The memory used to store the matrices is app workspace memory and
    // is not leaked.
    ON_MemoryAllocationTracking disable_tracking(false);

    // calculate the matrix and add it to the cache
    unsigned int R = 0;
    ON_SubDMatrixHashElement* new_hash_element = new(std::nothrow) ON_SubDMatrixHashElement();
    if (nullptr != new_hash_element)
    {
      R = new_hash_element->m_sm.SetFromSectorType(sector_type);
      if (0 == R)
      {
        delete new_hash_element;
        new_hash_element = new(std::nothrow) ON_SubDMatrixHashElement();
        if (nullptr != new_hash_element)
          new_hash_element->m_sm.m_sector_type = sector_type;
      }
      if (nullptr != new_hash_element)
      {
        if (nullptr == hash_table[hash_index])
          hash_table[hash_index] = new_hash_element;
        else
        {
          // insert elements used frequently first
          ON_SubDMatrixHashElement* prev_hash_element = nullptr;
          hash_element = hash_table[hash_index];
          while (nullptr != hash_element)
          {
            if (CompareMatrixHashElement(new_hash_element, hash_element) < 0)
            {
              new_hash_element->m_next = hash_element;
              if (nullptr != prev_hash_element)
                prev_hash_element->m_next = new_hash_element;
              else
                hash_table[hash_index] = new_hash_element;
              break;
            }
            prev_hash_element = hash_element;
            hash_element = hash_element->m_next;
            if (nullptr == hash_element)
            {
              prev_hash_element->m_next = new_hash_element;
              break;
            }
          }
        }
      }
      hash_element = new_hash_element;
    }
  }

  // Unlock the cache
  if (bReturnLock)
    lock.ReturnLock();
 
  if ( nullptr != hash_element )
    return hash_element->m_sm;

  return ON_SUBD_RETURN_ERROR(ON_SubDMatrix::Empty);
}

static unsigned int SetTypeAndValenceFailure()
{
  ON_SubDIncrementErrorCount();
  return 0;
}

unsigned int ON_SubDMatrix::SetFromSectorType(
  ON_SubDSectorType sector_type
  )
{
  m_sector_type = ON_SubDSectorType::Empty;
  m_R = 0;
  m_S = nullptr;
  m_LP = nullptr;
  m_L1 = nullptr;
  m_L2 = nullptr;

  if (false == sector_type.IsValid() )
    return SetTypeAndValenceFailure();

  const unsigned int R = sector_type.PointRingCount();
  if (R < 3)
    return SetTypeAndValenceFailure();

  if (m__max_R < R)
    m__max_R = 0;

  double* LP = m__buffer.Reserve(3*R);
  if ( nullptr == LP )
    return SetTypeAndValenceFailure();
  double* L1 = LP + R;
  double* L2 = L1 + R;

  const bool bLimitEvaluationCoefficientsAvailable = sector_type.SurfaceEvaluationCoefficientsAvailable();
  if (bLimitEvaluationCoefficientsAvailable)
  {
    if (R != sector_type.GetSurfaceEvaluationCoefficients(LP, R, L1, R, L2, R))
      return SetTypeAndValenceFailure();
  }
  else
  {
    m__buffer.Zero();
  }

  if (m__max_R < R)
  {
    if (!m__S.Create(R, R))
      return SetTypeAndValenceFailure();
    m__max_R = R;
  }
  
  if (R != sector_type.GetSubdivisionMatrix(m__S.m, R))
    return SetTypeAndValenceFailure();
  
  m_sector_type = sector_type;
  m_R = R;
  m_S = m__S.m;
  m_LP = LP;
  m_L1 = L1;
  m_L2 = L2;

  if (false == bLimitEvaluationCoefficientsAvailable)
  {
    // This is a temporary lame, slow and approximate hack - good thing it's cached.
    // WHen I finished calculating the general case for left eigenvectors
    // of the dart subdivision matrix, this will be deleted.
    ON_Matrix Sinfinity[2];
    Sinfinity[0].Multiply(m__S,m__S);
    for (unsigned int i = 1; i < 4; i++)
    {
      Sinfinity[(i % 2)].Multiply(m__S, Sinfinity[(i+1)%2]);
    }
    const double* Sinfinity0 = Sinfinity[1].m[0];
    double LPsum = 0.0;
    for (unsigned int i = 0; i < R; i++)
    {
      LP[i] = Sinfinity0[i];
      if ( !(LP[i] >= 0.0) )
        LP[i] = 0.0;
      LPsum += LP[i];
    }
    if (fabs(1.0 - LPsum) > 1e-15)
    {
      for (unsigned int i = 0; i < R; i++)
        LP[i] /= LPsum;
    }
  }

  return m_R;
}

static double TestMatrixReturnValue(
  double d,
  double rc
  )
{
  if (!(d >= 0.0 && rc >= 0.0))
    ON_SUBD_RETURN_ERROR(ON_UNSET_VALUE);

  if (d > rc)
  {
#if defined(ON_DEBUG)
    if (d > 0.0001)
    {
      // almost certainly a bug
      ON_SubDIncrementErrorCount();
    }
#endif

    rc = d;
  }

  return rc;
}

double ON_SubDMatrix::TestMatrix() const
{
  if (nullptr == m_S || m_R < 3)
    return ON_SUBD_RETURN_ERROR(ON_UNSET_VALUE);

  if ( false == m_sector_type.IsValid() )
    return ON_SUBD_RETURN_ERROR(ON_UNSET_VALUE);

  if (m_R != m_sector_type.PointRingCount())
    return ON_SUBD_RETURN_ERROR(ON_UNSET_VALUE);

  const double lambda = m_sector_type.SubdominantEigenvalue();
  if (!(lambda > 0.0 && lambda < 1.0))
    return ON_SUBD_RETURN_ERROR(ON_UNSET_VALUE);

  const unsigned int lambda_multiplicity = m_sector_type.SubdominantEigenvalueMulitiplicity();
  if ( lambda_multiplicity <= 0 )
    return ON_SUBD_RETURN_ERROR(ON_UNSET_VALUE);

  double rc = 0.0;


  const bool bTestLimitEvaluation = m_sector_type.SurfaceEvaluationCoefficientsAvailable();

  // Eigen information test
  ON_SimpleArray<double> buffer;
  double* E1 = buffer.Reserve(5*m_R);
  double* E2 = E1 + m_R;
  double* LP = E2 + m_R;
  double* L1 = LP + m_R;
  double* L2 = L1 + m_R;
  double d = m_sector_type.GetSubdominantEigenvectors(E1, m_R, E2, m_R);
  if (!(d == lambda))
    return ON_SUBD_RETURN_ERROR(ON_UNSET_VALUE);

  if (bTestLimitEvaluation)
  {
    if (!m_sector_type.GetSurfaceEvaluationCoefficients(LP, m_R, L1, m_R, L2, m_R))
      return ON_SUBD_RETURN_ERROR(ON_UNSET_VALUE);
  }
  else
  {
    for (unsigned int i = 0; i < m_R; i++)
    {
      LP[i] = 0.0;
      L1[i] = 0.0;
      L2[i] = 0.0;
    }
  }

  // A smooth sector with 2 faces is degenerate and does not have nice eigenvalues and eigenvectors
  // that give a well defined surface normal. In this case we use a heuristic for the normal.
  // When bSmoothTwoFaceCase E1 = {0,0,0,0,0}, lengthE1 = 0, lengthE1 = 0.
  const bool bSmoothTwoFaceCase
    = (m_sector_type.IsSmoothSector() || m_sector_type.IsDartSector())
    && 2u == m_sector_type.FaceCount()
    && 2u == m_sector_type.EdgeCount()
    ;
  const bool bDartTwoFaceCase
    = (m_sector_type.IsSmoothSector() || m_sector_type.IsDartSector())
    && 2u == m_sector_type.FaceCount()
    && 2u == m_sector_type.EdgeCount()
    ;
  const bool bSmoothOrDartTwoFaceCase = bSmoothTwoFaceCase || bDartTwoFaceCase;

  double lengthE1 = 0.0;
  double lengthE2 = 0.0;
  double lengthL1 = 0.0;
  double lengthL2 = 0.0;
  for (unsigned int i = 0; i < m_R; i++)
  {
    lengthE1 += E1[i] * E1[i];
    lengthE2 += E2[i] * E2[i];
    lengthL1 += L1[i] * L1[i];
    lengthL2 += L2[i] * L2[i];
  }
  if (false == bSmoothOrDartTwoFaceCase && !(lengthE1 > 0.0))
    return ON_SUBD_RETURN_ERROR(ON_UNSET_VALUE);
  if (!(lengthE2 > 0.0))
    return ON_SUBD_RETURN_ERROR(ON_UNSET_VALUE);
  if (!(lengthL1 > 0.0))
    return ON_SUBD_RETURN_ERROR(ON_UNSET_VALUE);
  if (!(lengthL2 > 0.0))
    return ON_SUBD_RETURN_ERROR(ON_UNSET_VALUE);
  lengthE1 = sqrt(lengthE1);
  lengthE2 = sqrt(lengthE2);
  lengthL1 = sqrt(lengthL1);
  lengthL2 = sqrt(lengthL2);
  if (false == bSmoothOrDartTwoFaceCase && !(lengthE1 > 0.0))
    return ON_SUBD_RETURN_ERROR(ON_UNSET_VALUE);
  if (!(lengthE2 > 0.0))
    return ON_SUBD_RETURN_ERROR(ON_UNSET_VALUE);
  if (!(lengthL1 > 0.0))
    return ON_SUBD_RETURN_ERROR(ON_UNSET_VALUE);
  if (!(lengthL2 > 0.0))
    return ON_SUBD_RETURN_ERROR(ON_UNSET_VALUE);
  
  double LPsum = 0.0;
  double L1sum = 0.0;
  double L2sum = 0.0;
  double E1oLP = 0.0;
  double E2oLP = 0.0;
  for (unsigned int i = 0; i < m_R; i++)
  {
    if (!(LP[i] >= 0.0))
      return ON_SUBD_RETURN_ERROR(ON_UNSET_VALUE);

    const double* Si = m_S[i];
    double x1 = 0.0;
    double x2 = 0.0;
    for (unsigned int j = 0; j < m_R; j++)
    {
      // E1, E2 should be eigenvectors of S with eigenvalue lambda
      x1 += Si[j] * E1[j];
      x2 += Si[j] * E2[j];
    }
    d = bSmoothOrDartTwoFaceCase ? 0.0 : fabs((x1 - lambda*E1[i])/lengthE1);
    rc = TestMatrixReturnValue(d,rc);
    if (!(rc >= 0.0))
      break;

    if (2 == lambda_multiplicity)
    {
      d = fabs((x2 - lambda*E2[i])/lengthE2);
      rc = TestMatrixReturnValue(d, rc);
      if (!(rc >= 0.0))
        break;
    }

    if ( false == bTestLimitEvaluation )
      continue;

    if (nullptr != m_LP)
    {
      if ( !(m_LP[i] == LP[i]) )
        return ON_SUBD_RETURN_ERROR(ON_UNSET_VALUE);
    }

    double y1 = 0.0;
    double y2 = 0.0;
    for (unsigned int j = 0; j < m_R; j++)
    {
      // L1, L2 should be eigenvectors of Transpose(S) with eigenvalue lambda
      y1 += m_S[j][i] * L1[j];
      y2 += m_S[j][i] * L2[j];
    }

    d = (bDartTwoFaceCase && (2u == i || 4u == i)) ? 0.0 : fabs((y1 - lambda*L1[i])/lengthL1);
    rc = TestMatrixReturnValue(d,rc);
    if (!(rc >= 0.0))
      break;

    if (2 == lambda_multiplicity)
    {
      d = fabs((y2 - lambda*L2[i])/lengthL2);
      rc = TestMatrixReturnValue(d, rc);
      if (!(rc >= 0.0))
        break;
    }


    LPsum += LP[i];
    L1sum += L1[i];
    L2sum += L2[i];

    E1oLP += E1[i] * LP[i];
    E2oLP += E2[i] * LP[i];
  }
    
  if (bTestLimitEvaluation)
  {
    while (rc >= 0.0)
    {
      // LP coefficients should sum to 1
      rc = TestMatrixReturnValue(fabs(1.0 - LPsum), rc);
      if (!(rc >= 0.0))
        break;

      // E1 and E2 should be orthogonal to LP which means
      // E0oLP and E1oLP should be zero
      //
      // Why?
      //   Set T = Transpose(S).
      //   T*LP = LP (LP is an eigenvector or T with eigenvalue = 1)
      //   S*E = lambda*E (E is an eigenvector of S with eigenvalue lambda != 1)
      //   LP o E1
      //    = Transpose(LP) * E
      //    = Transpose( T*LP ) * E
      //    = Transpose(LP) * Transpose(T) * E
      //    = Transpose(LP) * S * E
      //    = Transpose(LP) * (lambda E)
      //    = lambda * (Transpose(LP) * E )
      //    = lambda * LPoE
      //   If LPoE != 0, then lambda = 1, which is not the case.
      rc = bSmoothOrDartTwoFaceCase ? 0.0 : TestMatrixReturnValue(fabs(E1oLP) / lengthE1, rc);
      if (!(rc >= 0.0))
        break;
      rc = TestMatrixReturnValue(fabs(E2oLP) / lengthE2, rc);
      if (!(rc >= 0.0))
        break;

      // L1 and L2 should be orthogonal to (1,1,...,1) which means
      // L1 L2 coefficients should sum to zero.
      rc = TestMatrixReturnValue(fabs(L1sum) / lengthL1, rc);
      if (!(rc >= 0.0))
        break;
      rc = TestMatrixReturnValue(fabs(L2sum) / lengthL2, rc);
      if (!(rc >= 0.0))
        break;

      break;
    }

    // See if L1 and L2 can produce a reasonable normal in the simplest possible case
    double z = m_sector_type.SurfaceNormalSign();
    if (!(z > 0.0))
      return ON_SUBD_RETURN_ERROR(ON_UNSET_VALUE);
  }

  if (rc >= 0.0)
    return rc;

  return ON_SUBD_RETURN_ERROR(ON_UNSET_VALUE); 
}

double ON_SubDMatrix::TestEvaluation(
  ON_SubDSectorType sector_type,
  unsigned int minimum_sector_face_count,
  unsigned int maximum_sector_face_count,
  ON_TextLog* text_log
  )
{
  ON_SubDVertexTag vertex_tags[] = { 
    ON_SubDVertexTag::Smooth
    ,ON_SubDVertexTag::Crease
    ,ON_SubDVertexTag::Corner
    ,ON_SubDVertexTag::Dart
  };
  const char* vertex_tag_names[sizeof(vertex_tags) / sizeof(vertex_tags[0])] = {
    "smooth"
    ,"crease"
    ,"corner"
    ,"dart"
  };

  unsigned int corner_sector_angle_index0 = ON_UNSET_UINT_INDEX-1;
  unsigned int corner_sector_angle_index1 = ON_UNSET_UINT_INDEX;
  const double corner_sector_angle_radians 
    = (ON_SubDVertexTag::Corner == sector_type.VertexTag())
    ? sector_type.CornerSectorAngleRadians()
    : ON_SubDSectorType::UnsetCornerSectorAngle;


  ON_SubDVertexTag vertex_tag = sector_type.VertexTag();
  
  size_t subd_type_count = 1;
  size_t subd_type_index0 = 0;

  if ( 0 == subd_type_index0 && 2 == subd_type_count)
    subd_type_count = 1; // tri stuff no ready

  size_t vertex_tag_count = sizeof(vertex_tags) / sizeof(vertex_tags[0]);
  size_t vertex_tag_index0 = 0;

  if (ON_SubDVertexTag::Unset != vertex_tag)
  {
    for (size_t vertex_tag_index = vertex_tag_index0; vertex_tag_index < vertex_tag_count; vertex_tag_index++)
    {
      if (vertex_tag == vertex_tags[vertex_tag_index])
      {
        vertex_tag_index0 = vertex_tag_index;
        vertex_tag_count = vertex_tag_index + 1;
        if (ON_SubDVertexTag::Corner == vertex_tag && ON_SubDSectorType::IsValidCornerSectorAngleRadians(corner_sector_angle_radians) )
        {
          unsigned int angle_dex = sector_type.CornerSectorAngleIndex();
          if (angle_dex <= ON_SubDSectorType::MaximumCornerAngleIndex)
          {
            corner_sector_angle_index0 = angle_dex;
            corner_sector_angle_index1 = angle_dex+1;
          }
          else
          {
            corner_sector_angle_index1 = ON_UNSET_UINT_INDEX;
            corner_sector_angle_index0 = corner_sector_angle_index1-1;
          }
        }
        break;
      }
    }
  }

  const unsigned int Fmax 
    = ( 0 == maximum_sector_face_count)
    ? 20
    : maximum_sector_face_count;

  unsigned int pass_count = 0;
  unsigned int fail_count = 0;
  double max_d = 0.0;
  const unsigned int maximum_fail_count = 10;

  for (size_t vertex_tag_index = vertex_tag_index0; vertex_tag_index < vertex_tag_count; vertex_tag_index++)
  {
    const ON_SubDVertexTag vertex_tag_for_scope = vertex_tags[vertex_tag_index];
    const char* sVertexTagName = vertex_tag_names[vertex_tag_index];

    unsigned int Fmin = ON_SubDSectorType::MinimumSectorFaceCount(vertex_tag_for_scope);
    if ( minimum_sector_face_count > Fmin )
      Fmin = minimum_sector_face_count;

    unsigned int angle_i0 = corner_sector_angle_index0;
    unsigned int angle_i1 = corner_sector_angle_index1;
    if (ON_SubDVertexTag::Corner == vertex_tag_for_scope && ON_SubDSectorType::UnsetCornerSectorAngle == corner_sector_angle_radians)
    {
      angle_i0 = 2;
      angle_i1 = ON_SubDSectorType::MaximumCornerAngleIndex/2 - 1;
    }

    for (unsigned int F = Fmin; F <= Fmax; F++)
    {
      for (unsigned int corner_sector_angle_index = angle_i0; corner_sector_angle_index < angle_i1; corner_sector_angle_index++)
      {
        double angle_radians = corner_sector_angle_radians;
        if (ON_SubDVertexTag::Corner == vertex_tag_for_scope && ON_SubDSectorType::UnsetCornerSectorAngle == angle_radians)
          angle_radians = ON_SubDSectorType::AngleRadiansFromCornerAngleIndex(corner_sector_angle_index);

        ON_SubDSectorType test_sector_type = ON_SubDSectorType::Create( vertex_tag_for_scope, F, angle_radians);

        if (false == test_sector_type.SurfaceEvaluationCoefficientsAvailable())
          continue;
        const unsigned int N = test_sector_type.EdgeCount();
        const ON_SubDMatrix& SM = ON_SubDMatrix::FromCache(test_sector_type);
        double d = SM.TestEvaluation();
        if (d >= 0.0)
        {
          pass_count++;
          if (d > max_d)
            max_d = d;
        }
        else
        {
          fail_count++;
        }
        if (nullptr != text_log)
        {
          ON_String test_description;
          if (ON_SubDVertexTag::Corner == vertex_tag_for_scope)
            test_description.Format("%s, %u faces, %u edges, angle = %u/%u 2pi", sVertexTagName, F, N, corner_sector_angle_index, ON_SubDSectorType::MaximumCornerAngleIndex);
          else
            test_description.Format("%s, %u faces, %u edges", sVertexTagName, F, N);

          if (d >= 0.0)
            text_log->Print("Test( %s) passed. Deviation = %g\n", (const char*)test_description, d);
          else
            text_log->Print("Test( %s ) failed\n", (const char*)test_description);

          if (SM.m_R > 0)
          {
            // Print evaluation coefficients.
            const ON_TextLogIndent indent1(*text_log);
            text_log->Print("Limit suface evaluation coefficients:\n");
            const ON_TextLogIndent indent2(*text_log);
            for (unsigned Ldex = 0; Ldex < 3; ++Ldex)
            {
              const double* L;
              ON_String Lid;
              switch (Ldex)
              {
              case 0u:
                L = SM.m_LP;
                Lid = "point";
                break;
              case 1u:
                L = SM.m_L1;
                Lid = "tangent[1]";
                break;
              case 2u:
                L = SM.m_L2;
                Lid = "tangent[2]";
                break;
              default:
                L = nullptr;
                break;
              }
              if (nullptr == L)
                continue;
              char sep[] = { ' ', '=', ' ', 0 };
              unsigned termcount = 0;
              if ( 0.0 == L[0])
                text_log->Print("%s", static_cast<const char*>(Lid));
              else
              {
                if (1.0 == L[0])
                  text_log->Print("%s%sV", static_cast<const char*>(Lid), sep, L[0]);
                else if (-1.0 == L[0])
                  text_log->Print("%s%s-V", static_cast<const char*>(Lid), sep, L[0]);
                else
                  text_log->Print("%s%s%g*V", static_cast<const char*>(Lid), sep, L[0]);
                ++termcount;
              }
              bool bPopIndent = false;
              for (unsigned r = 1u; r < SM.m_R; ++r)
              {
                double c = fabs(L[r]);
                if (0.0 == L[r])
                  continue;
                ++termcount;
                if (termcount >= 2)
                {
                  c = fabs(c);
                  sep[1] = (L[r] < 0.0) ? '-' : '+';
                }

                if (8 == termcount && SM.m_R > 9 && false == bPopIndent)
                {
                  text_log->PrintNewLine();
                  text_log->PushIndent();
                  bPopIndent = true;
                }
                if (1.0 == c)
                  text_log->Print("%s", sep);
                else
                  text_log->Print("%s%g*", sep, c);
                if (1u == r % 2u)
                  text_log->Print("E%u", (r+1u)/2u);
                else
                  text_log->Print("Q%u", r/2u);
                if (14 == termcount && r < SM.m_R - 2)
                {
                  text_log->Print(" + ...");
                  r = SM.m_R - 2;
                }
              }
              text_log->PrintNewLine();
              if (bPopIndent)
                text_log->PopIndent();
            }
          }
        }
        if (ON_SubDVertexTag::Corner != vertex_tag_for_scope)
          break;
        if (fail_count >= maximum_fail_count)
          break;
      }
      if (fail_count >= maximum_fail_count)
        break;
    }
    if (fail_count >= maximum_fail_count)
      break;
  }


  if (text_log)
  {
    text_log->Print("%u tests. %d failed. Maximum deviation = %g\n",pass_count+fail_count, fail_count, max_d);
    if (fail_count >= maximum_fail_count)
      text_log->Print("Additional tests canceled because there were too many failures.\n");
  }

  if (fail_count >= maximum_fail_count)
    return ON_SUBD_RETURN_ERROR(ON_UNSET_VALUE);

  return max_d;
}


static void TestPrecision(
  double d,
  double& precision
  )
{
  if (d > 1e-3)
  {
    ON_SubDIncrementErrorCount();
  }
  if (d > precision)
    precision = d;
}

double ON_SubDMatrix::TestComponentRing(
  const ON_SubDComponentPtr* component_ring,
  size_t component_ring_count
  ) const
{
  const double rc_error = ON_UNSET_VALUE;

  if (!m_sector_type.IsValid())
    return ON_SUBD_RETURN_ERROR(rc_error);


  if (component_ring_count < 4 || component_ring_count != m_sector_type.ComponentRingCount())
    return ON_SUBD_RETURN_ERROR(rc_error);

  const unsigned int F = m_sector_type.FaceCount();
  const unsigned int N = m_sector_type.EdgeCount();
  const unsigned int R = m_sector_type.PointRingCount();
  
  if (m_R != R)
    return ON_SUBD_RETURN_ERROR(rc_error);

  const ON_SubDVertexTag vertex_tag = m_sector_type.VertexTag();
  const unsigned int face_edge_count = m_sector_type.FacetEdgeCount();
  const bool bSubdivideFaces = (R == F+N+1 && 4 == face_edge_count);

  const ON_SubDVertex* center_vertex = component_ring[0].Vertex();
  if (nullptr == center_vertex)
    return ON_SUBD_RETURN_ERROR(rc_error);

  if (vertex_tag != center_vertex->m_vertex_tag || center_vertex->IsStandard())
    return ON_UNSET_VALUE; // not an error - need a round of subdivision before matrix can be used

  ON_SimpleArray<ON_3dPoint> point_ring_array;
  if ( R != ON_SubD::GetSectorPointRing(false,component_ring_count,component_ring,point_ring_array) )
    return ON_SUBD_RETURN_ERROR(rc_error);
  const ON_3dPoint* vertexR = point_ring_array.Array();

  ON_3dPoint Q;
  if (false == center_vertex->EvaluateCatmullClarkSubdivisionPoint(&Q.x))
    return ON_SUBD_RETURN_ERROR(rc_error);

  double Pdelta = 0.0;
  double Edelta = 0.0;
  double Fdelta = 0.0;

  ON_3dPoint P = ON_3dPoint::Origin;
  if (false == EvaluateSubdivisionPoint(0, &vertexR[0].x, R,3,P))
    return ON_SUBD_RETURN_ERROR(rc_error);
  double d = P.DistanceTo(Q);
  TestPrecision(d, Pdelta);

  for (unsigned int i = 1; i < component_ring_count; i++)
  {
    const ON_SubDEdge* edge = component_ring[i].Edge();
    if (nullptr == edge)
      return ON_SUBD_RETURN_ERROR(rc_error);

    if (false == edge->EvaluateCatmullClarkSubdivisionPoint(&Q.x))
      return ON_SUBD_RETURN_ERROR(rc_error);

    P = ON_3dPoint::Origin;
    if (false == EvaluateSubdivisionPoint(i, &vertexR[0].x, R,3,P))
      return ON_SUBD_RETURN_ERROR(rc_error);

    double dist_PQ = P.DistanceTo(Q);
    TestPrecision(dist_PQ, Edelta);

    if ( !bSubdivideFaces || i+1 >= component_ring_count )
      continue;

    i++;
    const ON_SubDFace* face = component_ring[i].Face();
    if (nullptr == face)
      return ON_SUBD_RETURN_ERROR(rc_error);

    if (face_edge_count != face->m_edge_count)
      return ON_SUBD_RETURN_ERROR(rc_error);

    if (false == face->EvaluateCatmullClarkSubdivisionPoint(&Q.x))
      return ON_SUBD_RETURN_ERROR(rc_error);

    P = ON_3dPoint::Origin;
    if (false == EvaluateSubdivisionPoint(i, &vertexR[0].x, R,3,P))
      return ON_SUBD_RETURN_ERROR(rc_error);

    dist_PQ = P.DistanceTo(Q);
    TestPrecision(dist_PQ, Fdelta);
  }

  double max_delta = Pdelta;
  if (Edelta > max_delta)
    max_delta = Edelta;
  if (Fdelta > max_delta)
    max_delta = Fdelta;

  return max_delta;
}

double ON_SubDMatrix::TestEvaluation(
  const unsigned int subd_recursion_count,
  ON_SubDSectorIterator sit,
  ON_SimpleArray<ON_SubDComponentPtr>& component_ring,
  ON_SimpleArray< ON_3dPoint >& subd_points,
  ON_SubDSectorSurfacePoint& limit_point
  )
{
  const double rc_error = ON_UNSET_VALUE;
  limit_point = ON_SubDSectorSurfacePoint::Unset;

  component_ring.SetCount(0);
  subd_points.SetCount(0);

  const ON_SubDSectorType sector_type = ON_SubDSectorType::Create(sit);

  const unsigned int component_ring_count = ON_SubD::GetSectorComponentRing(sit,component_ring);
  if ( component_ring_count < 4 || component_ring_count != sector_type.ComponentRingCount())
    return ON_SUBD_RETURN_ERROR(rc_error);

  const unsigned int N = ON_SubD::ComponentRingEdgeCount(component_ring_count);
  const unsigned int F = ON_SubD::ComponentRingFaceCount(component_ring_count);
  if ( N != sector_type.EdgeCount())
    return ON_SUBD_RETURN_ERROR(rc_error);
  if ( F != sector_type.FaceCount())
    return ON_SUBD_RETURN_ERROR(rc_error);    
  const unsigned int R = N + F;
  if (R != sector_type.PointRingCount())
    return ON_SUBD_RETURN_ERROR(rc_error);

  const unsigned int point_ring_stride = 3;
  ON_3dPoint* point_ring = subd_points.Reserve(R*(subd_recursion_count+1));
  const ON_3dPoint* point_ring0 = point_ring;
  const ON_3dPoint* point_ringEnd = point_ring + R*(subd_recursion_count+1);

  unsigned int rc = ON_SubD::GetSectorPointRing(
    true, // bSubdivideIfNeeded,
    component_ring.Array(),
    component_ring_count,
    &point_ring[0].x,
    R,
    3 // point_ring_stride,
    );

  if (rc != R)
    return ON_SUBD_RETURN_ERROR(rc_error);

  const ON_SubDVertex* center_vertex = sit.CenterVertex();
  const ON_SubDFace* sector_face = sit.CurrentFace();

  if (subd_recursion_count > 0)
  {
    ON_SubD_FixedSizeHeap fsh[2];
    const ON_SubDComponentPtr* element = component_ring.Array();
    ON_SimpleArray< ON_SubDComponentPtr > component_ring_buffer;
    const ON_SubDVertex* v0 = nullptr;
    for (unsigned int recursion_level = 0; recursion_level < subd_recursion_count; recursion_level++)
    {
      const ON_SubDVertex* v1 = ON_SubD::SubdivideSector( v0, element, component_ring_count, fsh[recursion_level%2]);
      if ( nullptr == v1 || N != v1->m_edge_count || F != v1->m_face_count)
        return ON_SUBD_RETURN_ERROR(rc_error);
      if (0 == recursion_level)
      {        
        if (point_ring0[0].x == v1->m_P[0] && point_ring0[0].y == v1->m_P[1] && point_ring0[0].z == v1->m_P[2])
        {
          // subdivision was required to get initial point ring.
          v0 = v1;
          v1 = ON_SubD::SubdivideSector( v0, element, component_ring_count, fsh[recursion_level % 2]);
          if (nullptr == v1 || N != v1->m_edge_count || F != v1->m_face_count)
            return ON_SUBD_RETURN_ERROR(rc_error);
        }
      }
      v0 = v1;

      subd_points.AppendNew() = v1->m_P;
      for (unsigned i = 0; i < N; i++)
      {
        const ON_SubDEdge* e = v1->Edge(i);
        if ( nullptr == e )
          return ON_SUBD_RETURN_ERROR(rc_error);
        const ON_SubDVertex* v = e->m_vertex[1];
        if ( nullptr == v )
          return ON_SUBD_RETURN_ERROR(rc_error);
        subd_points.AppendNew() = v->m_P;
        if (i < F)
        {
          const ON_SubDFace* f = v1->Face(i);
          if ( nullptr == f )
            return ON_SUBD_RETURN_ERROR(rc_error);
          v = f->Vertex(2);
          if ( nullptr == v )
            return ON_SUBD_RETURN_ERROR(rc_error);
          subd_points.AppendNew() = v->m_P;
        }
      }
    }
  }
  

  const ON_SubDMatrix& SM = ON_SubDMatrix::FromCache(sector_type);
  if (false == SM.IsValid() || nullptr == SM.m_S || R != SM.m_R)
      return ON_SUBD_RETURN_ERROR(rc_error);

  double maxd = 0.0;
  double d;
  // calculate subdivision deviation (should be nearly zero)
  {
    const ON_3dPoint* point_ring1 = point_ring0;
    for (const ON_3dPoint* point_ring2 = point_ring1 + R; point_ring2 < point_ringEnd; point_ring1 += R, point_ring2 += R)
    {
      for (unsigned int i = 0; i < R; i++)
      {
        ON_3dPoint P(ON_3dPoint::Origin);
        if ( false == SM.EvaluateSubdivisionPoint(i, &point_ring1[0].x, R,point_ring_stride,P) )
          return ON_SUBD_RETURN_ERROR(rc_error);
        d = P.DistanceTo(point_ring2[i]);
        if (d > maxd)
          maxd = d;
      }
      point_ring1 = point_ring2;
    }
  }

  // calculate limit point using ON_SubDVertex evaluation code
  ON_SubDSectorSurfacePoint center_vertex_limit_point = ON_SubDSectorSurfacePoint::Unset; 
  center_vertex->GetSurfacePoint(sector_face,center_vertex_limit_point);
  
  // calculate limit point using matrix
  if ( false == SM.EvaluateSurfacePoint(&point_ring0[0].x, R, point_ring_stride, false, limit_point ) )
    return ON_SUBD_RETURN_ERROR(rc_error);

  // calculate limit point deviation (should be nearly zero)
  const ON_3dPoint center_vertex_P(center_vertex_limit_point.m_limitP);
  const ON_3dPoint matrix_P(limit_point.m_limitP);
  d = center_vertex_P.DistanceTo(matrix_P);
  if (!ON_IsValid(d))
    return ON_SUBD_RETURN_ERROR(rc_error);
  if (d > maxd)
    maxd = d;

  // calculate limit normal deviation (should be nearly zero)
  const ON_3dVector center_vertex_N(center_vertex_limit_point.m_limitN);
  const ON_3dVector matrix_N(limit_point.m_limitN);
  d = (matrix_N - center_vertex_N).Length();
  if (!ON_IsValid(d))
    return ON_SUBD_RETURN_ERROR(rc_error);
  if (d > maxd)
    maxd = d;

  return maxd;
}

//#define ON_SUBD_JORDON_DECOMP_CODE
#if defined (ON_SUBD_JORDON_DECOMP_CODE)

// This code is not required for ON_SubD evaulation.
// It was of theoretical interest early in the project.

class ON_NumberPolisher
{
public:
  ON_NumberPolisher(unsigned int valence, unsigned int R, const double* const * S)
    : m_N(valence)
    , m_R(R)
    , m_S(S)
  {
    unsigned int a = valence;
    while (a > 0 && 0 == a % 2)
      a /= 2;
    m_polish_base = 1024.0*a*a;
    const double polish[] = { 1.0, static_cast<double>(a), static_cast<double>(a*a), static_cast<double>(2 * valence + 1), static_cast<double>(4 * valence - 7), 3.0, 5.0, 7.0, 9.0, 11.0, 13.0, 15.0, 17.0, 19.0, 21.0, 23.0, 25.0, 27.0 };
    m_polish_count = sizeof(polish) / sizeof(polish[0]);
    m_up = std::unique_ptr< double >(new double[m_polish_count + 2 * valence + 1]);
    double* x = m_up.get();
    m_polish = x;
    m_E = x + m_polish_count;
    for (size_t i = 0; i < m_polish_count; i++)
    {
      x[i] = polish[i];
    }
  }

  bool PolishEigenvector(
    double lambda,
    double* eigenvector,
    double* eigenprecision
    ) const;

  bool PolishGeneralizedEigenvector(
    double lambda,
    const double* eigenvector,
    double* generalized_eigenvector,
    double* generalized_eigenprecision
    ) const;

  double PolishZeroOneValue(
    double v
    ) const
  {
    const double polish = 1.0;
    return ON_NumberPolisher::PolishValue(m_polish_01_base, m_polish_01_tol, &polish, 1, v);
  }

  double PolishRationalValue(
    double v
    ) const
  {
    return ON_NumberPolisher::PolishValue(m_polish_base, m_polish_tol, m_polish, m_polish_count, v);
  }

private:
  const unsigned int m_N = 0;
  const unsigned int m_R = 0;
  const double* const * m_S = nullptr;
  bool m_bTransposeS = false;

  double m_polish_base = 1024.0;
  double m_polish_tol = 1.0e-8;
  const double* m_polish = nullptr;
  size_t m_polish_count;

  double m_polish_01_base = 16.0;
  double m_polish_01_tol = 1.0e-12;
  double m_polish_01[3];

  double* m_E = nullptr;

  std::unique_ptr< double > m_up;

  static double PolishValue(
    const double polish_base,
    const double polish_tol,
    const double* polish,
    const size_t polish_count,
    double v);

};

double ON_NumberPolisher::PolishValue(
  const double polish_base,
  const double polish_tol,
  const double* polish,
  const size_t polish_count,
  double v)
{
  if (0.0 == v)
    return 0.0;
  if (floor(v) == v)
    return v;

  double tol = polish_base*polish_tol;
  if (tol > 0.015625)
    tol = 0.015625;

  for (size_t i = 0; i < polish_count; i++)
  {
    double t = polish[i];
    if (!(t > 0.0))
      continue;

    const double x = (t * fabs(v))*polish_base;
    double f = floor(x);
    if (f == x)
      return v;

    double e = x - f;
    if (e >= 0.5)
    {
      f += 1.0;
      e = f - x;
    }

    if (!(e >= 0.0))
      continue;

    if (!(e <= tol))
      continue;

    double polished_v = (f / t) / polish_base;
    if (0.0 != polished_v && v < 0.0)
      polished_v = -polished_v;

    if (v == polished_v)
      return v;

    if (fabs(v - polished_v) <= polish_tol)
      return polished_v; // polish modified v
  }

  return v;
}


bool ON_NumberPolisher::PolishEigenvector(
  double lambda,
  double* eigenvector,
  double* eigenprecision
  ) const
{
  bool bPolishApplied = false;

  bool bRationalPolishApplied = false;

  for (unsigned int j = 0; j < m_R; j++)
  {
    double v = PolishZeroOneValue(eigenvector[j]);
    if (v != eigenvector[j])
    {
      bPolishApplied = true;
      eigenvector[j] = v;
    }
    else
    {
      v = PolishRationalValue(eigenvector[j]);
      if (v != eigenvector[j])
        bRationalPolishApplied = true;
    }
    m_E[j] = v;
  }

  double eprecision = ON_EigenvectorPrecision(m_R, m_S, m_bTransposeS, lambda, eigenvector);

  if (bRationalPolishApplied)
  {
    double Eprecision = ON_EigenvectorPrecision(m_R, m_S, m_bTransposeS, lambda, m_E);
    if (Eprecision <= eprecision)
    {
      for (unsigned int j = 0; j < m_R; j++)
      {
        eigenvector[j] = m_E[j];
      }
      eprecision = Eprecision;
    }
  }

  if (eigenprecision)
    *eigenprecision = eprecision;

  return (bPolishApplied || bRationalPolishApplied);
}


bool ON_NumberPolisher::PolishGeneralizedEigenvector(
  double lambda,
  const double* xeigenvector,
  double* generalized_eigenvector,
  double* generalized_eigenprecision
  ) const
{
  bool bPolishApplied = false;

  bool bRationalPolishApplied = false;

  for (unsigned int j = 0; j < m_R; j++)
  {
    double v = PolishZeroOneValue(generalized_eigenvector[j]);
    if (v != generalized_eigenvector[j])
    {
      bPolishApplied = true;
      generalized_eigenvector[j] = v;
    }
    else
    {
      v = PolishRationalValue(generalized_eigenvector[j]);
      if (v != generalized_eigenvector[j])
        bRationalPolishApplied = true;
    }
    m_E[j] = v;
  }

  double eprecision = ON_MatrixSolutionPrecision(m_R, m_S, m_bTransposeS, lambda, generalized_eigenvector, xeigenvector);

  if (bRationalPolishApplied)
  {
    double Eprecision = ON_MatrixSolutionPrecision(m_R, m_S, m_bTransposeS, lambda, m_E, xeigenvector);
    if (Eprecision <= eprecision)
    {
      for (unsigned int j = 0; j < m_R; j++)
      {
        generalized_eigenvector[j] = m_E[j];
      }
      eprecision = Eprecision;
    }
  }

  if (generalized_eigenprecision)
    *generalized_eigenprecision = eprecision;

  return (bPolishApplied || bRationalPolishApplied);
}

static bool GetQuadDominantEigenvector(
  unsigned int R,
  const double* const* S,
  double** eigenvectors,
  double* eigenprecision,
  double* eigenpivots
  )
{
  // Any matrix whose rows sum to 1 has (1,1,...1) as an eigenvector
  // and the quad subd matrix is such a matrix.  For this matrix,
  // 1 is the dominant eigenvalue.
  // The call to ON_GetEigenvectors is still made to insure that
  // the ON_GetEigenvectors() code is robust enough to calculate this
  // "easy" eigenvector.

  const double lambda = 1.0;
  const unsigned int lambda_muliplicity = 1;

  const bool bTransposeS = false;

  // Use easy case as a validation check
  unsigned int ec = ON_GetEigenvectors(R, S, bTransposeS, lambda, lambda_muliplicity, nullptr, eigenvectors, eigenprecision, eigenpivots);

  if (1 != ec)
    return ON_SUBD_RETURN_ERROR(false);

  double* e1 = eigenvectors[0];

  double e1accuracy = 0.0;
  for (unsigned int i = 0; i < R; i++)
  {
    double x = fabs(1.0 - e1[i]);
    if (x > e1accuracy)
      e1accuracy = x;
    e1[i] = 1.0;
  }

  if (e1accuracy > 1e-4)
  {
    // ON_GetEigenvectors returned junk on the easiest case.
    // We cannot expect anything good to come out for the
    // other eigenvalues and S is probably corrupt.
    return ON_SUBD_RETURN_ERROR(false);
  }

  double e1precision = ON_EigenvectorPrecision(R,S,bTransposeS,lambda,e1);

  if (e1precision > 1e-4)
  {
    // S is junk.
    return ON_SUBD_RETURN_ERROR(false);
  }

  if (nullptr != eigenprecision)
    *eigenprecision = e1precision;

  return true;
}

static bool ON_SolveGetGeneralizedEigenvector(
  const unsigned int N,
  const double*const* S,
  bool bTransposeS,
  double lambda,
  const double* eigenvector,
  double* generalized_eigenvector,
  double* generalized_eigenprecision,
  double* generalized_eigenpivots
  )
{
  if (N < 1 || nullptr == S || !ON_IsValid(lambda) || nullptr == eigenvector)
    return false;

  unsigned int i, j, maxi, maxj, n0;
  double x;
  const double* src;
  const double* src1;
  double* dst;

  ON_Matrix _M(N, N);
  double** M = _M.m;

  ON_SimpleArray< double > _B(N);
  double* B = _B.Array();

  // Xdex records column permutations
  ON_SimpleArray< unsigned int > _Xdex(N);
  unsigned int* Xdex = _Xdex.Array();

  if (bTransposeS)
  {
    // M = Transpose(S - lambda*I)
    for (i = 0; i < N; i++)
    {
      Xdex[i] = i;
      B[i] = eigenvector[i];
      dst = M[i];
      for (unsigned int j = 0; j < N; j++)
      {
        *dst++ = S[j][i];
      }
      M[i][i] -= lambda;
    }
  }
  else
  {
    // M = S - lambda*I
    for (i = 0; i < N; i++)
    {
      Xdex[i] = i;
      B[i] = eigenvector[i];
      src = S[i];
      src1 = src + N;
      dst = M[i];
      while (src < src1)
      {
        *dst++ = *src++;
      }
      M[i][i] -= lambda;
    }
  }

  // reduce system of equations to upper triangular
  double gpivots[3] = { 0 };
  for (n0 = 0; n0 < N-1; n0++)
  {
    // find pivot = biggest entry in sub-matrix
    maxi = n0;
    maxj = n0;
    x = 0.0;
    for (i = n0; i < N; i++)
    {
      src = M[i];
      src1 = src + N;
      for ( src += n0; src < src1; src++ )
      {
        if (fabs(*src) > x)
        {
          x = fabs(*src);
          maxi = i;
          maxj = (unsigned int)(src - M[i]);
        }
      }
    }

    if (!(x > 0.0))
      break;

    if (0 == n0)
    {
      gpivots[0] = x;
      gpivots[1] = x;
    }
    else if (x < gpivots[1])
      gpivots[1] = x;
    else if (x > gpivots[0])
      gpivots[0] = x;

    // put pivot in M[n0][n0]
    if (n0 != maxi)
    {
      // swap rows n0 and maxi
      dst = M[n0]; M[n0] = M[maxi]; M[maxi] = dst;
      x = B[n0]; B[n0] = B[maxi]; B[maxi] = x;
    }
    if (n0 != maxj)
    {
      // swap columns n0 and maxj
      for (i = 0; i < N; i++)
      {
        dst = M[i];
        x =dst[n0]; dst[n0] = dst[maxj]; dst[maxj] = x;
      }
      j = Xdex[n0]; Xdex[n0] = Xdex[maxj]; Xdex[maxj] = j;
    }

    src1 = M[n0] + N;
    for (i = n0 + 1; i < N; i++)
    {
      src = M[n0] + n0;
      dst = M[i] + n0;

      x = -(*dst++) / (*src++);

      if (0.0 != x)
      {
        B[i] += x*B[n0];
        while ( src < src1 )
          *dst++ += x*(*src++);
      }
    }
  }

  // For debugging, save B
  ON_SimpleArray< double > savedB;
  savedB.Append(N, B);

  // In an ideal world, M[N-1][N-1] and B[N-1]
  // are zero at this point.
  // In reality, it should be much smaller than gpivots[1].
  x = fabs(M[N - 1][N - 1]);
  if (fabs(B[N - 1]) > x)
    x = fabs(B[N - 1]);
  gpivots[2] = x;

  if (nullptr != generalized_eigenpivots)
  {
    generalized_eigenpivots[0] = gpivots[0];
    generalized_eigenpivots[1] = gpivots[1];
    generalized_eigenpivots[2] = gpivots[2];
  }

  i = N - 1;
  B[i] = 0.0;
  src1 = B + i;
  while (i > 0)
  {
    src = B + i;
    const double* Mi = M[i-1] + i;
    x = 0.0;
    while (src < src1)
    {
      x += (*src++)*(*Mi++);
    }
    i--;
    B[i] = (B[i] - x) / M[i][i];
  }

  // solution with column permutation applied is in B[] 
  for (i = 0; i < N; i++)
    generalized_eigenvector[Xdex[i]] = B[i];

  if (nullptr != generalized_eigenprecision)
    *generalized_eigenprecision = ON_MatrixSolutionPrecision(N, S, bTransposeS, lambda, generalized_eigenvector, eigenvector);
  
  return true;
}

static unsigned int ON_GetGeneralizedEigenvectors(
  const ON_NumberPolisher& polish,
  const unsigned int N,
  const double*const* M,
  bool bTransposeM,
  double lambda,
  unsigned int lambda_multiplicity,
  double** eigenvectors,
  double* eigenprecision,
  double* eigenpivots
  )
{
  if (N < 1)
    return ON_SUBD_RETURN_ERROR(0);

  if (nullptr == M)
    return ON_SUBD_RETURN_ERROR(0);

  if (!(lambda == lambda && ON_IsValid(lambda)))
    return ON_SUBD_RETURN_ERROR(0);

  if (lambda_multiplicity < 1 || lambda_multiplicity > N)
    return ON_SUBD_RETURN_ERROR(0);

  // Get eigenvectors
  double epivots[3] = { 0 };
  unsigned int ec = ON_GetEigenvectors(N, M, bTransposeM, lambda, lambda_multiplicity, nullptr, eigenvectors, eigenprecision, epivots);
  if (0 == ec || ec > lambda_multiplicity)
    return ON_SUBD_RETURN_ERROR(0);

  if (ec > 0 && ec <= lambda_multiplicity)
  {
    for (unsigned int n = 0; n < ec; n++)
    {
      double ep = 0.0;
      //polish.PolishEigenvector(lambda, eigenvectors[n], &ep);
      if (eigenprecision)
        eigenprecision[n] = ep;
    }

    if (2 == lambda_multiplicity && 1 == ec)
    {
      // This case happens for quad subdivision matrices at crease vertices.
      // Get the generalized eigenvector by solving (M - lambda*I)*g = e
      double gpivots[3] = { 0 };
      double gep = 0.0;
      bool rc = ON_SolveGetGeneralizedEigenvector(
        N,
        M,
        bTransposeM,
        lambda,
        eigenvectors[0],
        eigenvectors[1],
        &gep,
        gpivots
        );
      if (rc)
      {
        //polish.PolishGeneralizedEigenvector(lambda, eigenvectors[0], eigenvectors[1], &gep);
        ec++;
      }
      if (eigenprecision)
        eigenprecision[1] = gep;
    }
  }

  return ec;
}

/*
Description:
  Calculate the Jordon decomposition for the subdivision matrix.
Parameters:
  eigenvalues - [in]
    R eigenvalues of S sorted in decreasing order. 
    1.0 = eigenvalues[0].
  super_diagonal - [out]
    If super_diagonal is not nullpter, then the R-1 values of the Jordon block
    super diagonal are returned here (zeros and ones).
  eigenvectors - [out]
    If eigenvectors is not nullptr, then R generalized eigenvectors are 
    returned so that if lambda = eigenvalues[i] and V = eigenvectors[i],
    then lambda*V = S * V.
  eigenprecision - [out]
    If eigenprecision is not nullptr, then eigenprecision[i] reports
    on the accuracy of the corresponding eigenvector.
    eigenprecision[i] = maximum value fabs(lambda*E[j] - (S*E[i])[j]), 0 <= j < 2N+1.
  eigenpivots - [out]
    If eigenprecision is not nullptr, then eigenpivots[i] reports
    on the pivots found when calculating the eigenvectors.
    eigenpivots[i][0] = maximum nonzero pivot
    eigenpivots[i][1] = minimum nonzero pivot
    eigenpivots[i][2] = minimum "zero" pivot
  E - [out]
    If E is not nullptr, then E[][] is the NxN matrix whose columns are
    the eigenvectors of S.
  Einverse - [out]
    If Einverse is not nullptr, then Einvers[][] is the inverse of the
    NxN matrix whose columns are the eigenvectors of S.
Returns:
  R > 0: The size of the subdivision matrix is RxR.
  0: failure.
Remarks:
  S = E * J * Inverse(E), where J is the Jordon matrix with diagonal = eigenvalues[], 
  and super diagonal = super_diagonal[], and zeros elsewhere.
*/
unsigned int ON_SubDMatrix_GetJordonDecomposition(
  const ON_SubDMatrix& subd_matrix,
  const double* eigenvalues,
  double* super_diagonal,
  double** eigenvectors,
  double* eigenprecision,
  double** eigenpivots,
  double** E,
  double** Einverse
  )
{

  unsigned int R = subd_matrix.m_R;

  if (R < 3 )
    return ON_SUBD_RETURN_ERROR(0);

  const bool bTransposeS = false;
  const double* const* S = subd_matrix.m_S;

  if (nullptr == S)
    return ON_SUBD_RETURN_ERROR(0);

  if (nullptr == eigenvalues)
    return ON_SUBD_RETURN_ERROR(0);

  if (nullptr == S[0])
    return ON_SUBD_RETURN_ERROR(0);

  if (!(1.0 == eigenvalues[0]))
    return ON_SUBD_RETURN_ERROR(0);

  for (unsigned int i = 1; i < R; i++)
  {
    if (nullptr == S[i])
      return ON_SUBD_RETURN_ERROR(0);
    if (!(eigenvalues[i] <= eigenvalues[i-1]))
      return ON_SUBD_RETURN_ERROR(0);
  }

  const bool bNeed_Einverse = (nullptr != Einverse);

  const bool bNeed_eigenvectors = (bNeed_Einverse || nullptr != E || nullptr != eigenprecision || nullptr != eigenpivots || nullptr != super_diagonal);

  ON_Matrix _eigenvectors;
  if (bNeed_eigenvectors)
  {
    if (nullptr == eigenvectors)
    {
      _eigenvectors.Create(R, R);
      eigenvectors = _eigenvectors.m;
    }
  }

  ON_SimpleArray< double > _super_diagonal;
  if (bNeed_eigenvectors && nullptr == super_diagonal)
    super_diagonal = _super_diagonal.Reserve(R - 1);

  ////////////////////////////////////////////////////////////////////////
  //
  // Get eigenvectors[]
  //
  if (nullptr != eigenvectors)
  {
    const ON_NumberPolisher polish(R/2, R, S);

    ON_SimpleArray<double> _eprecision;
    if (nullptr == eigenprecision)
      eigenprecision = _eprecision.Reserve(R);

    if (false == GetQuadDominantEigenvector(R, S, eigenvectors, eigenprecision, eigenpivots ? eigenpivots[0] : nullptr))
      return ON_SUBD_RETURN_ERROR(0);

    unsigned int eigenvector_count = 1;
    double lambda = 1.0;

    while (eigenvector_count < R)
    {
      if (!(eigenvalues[eigenvector_count] < lambda))
        return ON_SUBD_RETURN_ERROR(0);

      lambda = eigenvalues[eigenvector_count];
      unsigned int lambda_multiplicity = 1;
      while (eigenvector_count + lambda_multiplicity < R && lambda == eigenvalues[eigenvector_count + lambda_multiplicity])
        lambda_multiplicity++;

      double epivots[3] = { 0 };
      unsigned int ec = ON_GetGeneralizedEigenvectors(polish, R, S, bTransposeS, lambda, lambda_multiplicity, eigenvectors + eigenvector_count, eigenprecision + eigenvector_count, epivots);
      if (ec != lambda_multiplicity)
      {
        return ON_SUBD_RETURN_ERROR(0);
      }

      for (unsigned int n = eigenvector_count; n < eigenvector_count + lambda_multiplicity; n++)
      {
        if (nullptr != eigenpivots)
        {
          eigenpivots[n][0] = epivots[0];
          eigenpivots[n][1] = epivots[1];
          eigenpivots[n][2] = epivots[2];
        }
      }
      eigenvector_count += lambda_multiplicity;
    }

    ////////////////////////////////////////////////////////////////////////
    //
    // Get E[]
    //
    if (nullptr != E)
    {
      for (unsigned int i = 0; i < R; i++)
      {
        const double* Ecol = eigenvectors[i];
        for (unsigned int j = 0; j < R; j++)
        {
          E[j][i] = Ecol[j];
        }
      }
    }

    if (bNeed_Einverse)
    {
      ON_Matrix _Einverse;

      if (eigenvectors == _eigenvectors.m && nullptr == Einverse)
      {
        // use eigenvectors memory
        _Einverse.Create(R, R, eigenvectors, false);
        _Einverse.Transpose();
        Einverse = _Einverse.m;
      }
      else
      {
        if (nullptr == Einverse)
        {
          _Einverse.Create(R, R);
          Einverse = _Einverse.m;
        }
        else
          _Einverse.Create(R, R, Einverse, false);
        for (unsigned int i = 0; i < R; i++)
        {
          const double* Ecoli = eigenvectors[i];
          for (unsigned int j = 0; j < R; j++)
          {
            _Einverse.m[j][i] = Ecoli[j];
          }
        }
      }

      if (false == _Einverse.Invert(0.0))
        return ON_SUBD_RETURN_ERROR(0);


    }
  }

  return R;
}
#endif

