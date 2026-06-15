# ElaWidgetTools 커스텀 클래스 정리

대상 경로: `external/ElaWidgetTools`

기준 파일:

- 공개 헤더: `external/ElaWidgetTools/ElaWidgetTools/*.h`
- 개발/내부 보조 헤더: `external/ElaWidgetTools/ElaWidgetTools/DeveloperComponents/*.h`
- 커맨드 보조 헤더: `external/ElaWidgetTools/ElaWidgetTools/DeveloperComponents/Command/*.h`
- 라이브러리 버전 상수: `ElaDefVersion = "2.0.3"`

ElaWidgetTools는 Qt Widgets 기반 Fluent UI 스타일 컴포넌트 라이브러리다. 빌드 설정상 `ElaWidgetTools` 루트, `private`, `DeveloperComponents`, `DeveloperComponents/Command`가 include 경로에 포함되지만, 설치 대상 export header는 주로 `ElaWidgetTools/*.h`이다. 실제 애플리케이션에서는 아래의 "공개 사용 권장 클래스"를 우선 사용하고, `DeveloperComponents` 계열은 커스텀 확장이나 내부 동작 이해가 필요할 때 참고하는 편이 안전하다.

## 공통 사용 방식

- 대부분의 공개 클래스는 `ELA_EXPORT`가 붙은 DLL export 클래스다.
- `ElaProperty.h`의 매크로로 `Q_PROPERTY`, `setXxx`, `getXxx`, `pXxxChanged` signal이 생성된다.
- `ElaDef.h`는 테마, 아이콘, 메시지바 위치, 네비게이션 타입 등 공통 enum namespace를 제공한다.
- Windows에서는 DXGI, D3D11 관련 기능이 링크된다.

## 공개 사용 권장 클래스

| 클래스 | 기반 클래스 | 용도 | 주요 내용 |
|---|---:|---|---|
| `ElaAcrylicUrlCard` | `QPushButton` | 이미지가 있는 아크릴 URL 카드 | 제목/부제/이미지/URL을 가진 클릭형 카드. 외부 링크나 홍보 카드에 적합하다. |
| `ElaActionCommand` | `QObject` | 명령 객체 베이스 | `ElaActionCommander`가 실행하는 command 단위. route, stack 변경 같은 동작을 캡슐화한다. |
| `ElaActionCommander` | `QObject` | 명령 실행 관리자 | action command를 등록/실행하는 커맨드형 작업 관리자. |
| `ElaAppBar` | `QWidget` | 커스텀 윈도우 상단바 | 무프레임 창의 제목 표시, 드래그, 최소화/최대화/닫기, 사이즈 조절과 연동된다. |
| `ElaApplication` | `QObject` | 애플리케이션 전역 초기화 | Mica/Acrylic 등 window display mode, 전역 초기화, 테마 적용의 시작점으로 쓰인다. |
| `ElaBreadcrumbBar` | `QWidget` | breadcrumb navigation | 경로형 navigation UI. 항목 클릭 이벤트를 처리한다. |
| `ElaCalendar` | `QWidget` | 달력 뷰 | 날짜 선택/표시용 달력 위젯. `ElaCalendarPicker`의 내부 달력으로도 쓰인다. |
| `ElaCalendarPicker` | `QPushButton` | 날짜 선택 버튼 | 버튼 클릭 시 달력 팝업/컨테이너를 통해 날짜를 선택하는 picker. |
| `ElaCheckBox` | `QCheckBox` | Fluent 스타일 체크박스 | Qt `QCheckBox` 대체용 스타일드 컴포넌트. |
| `ElaColorDialog` | `QDialog` | 색상 선택 대화상자 | 색상 팔레트, picker, preview 등을 포함하는 color dialog. |
| `ElaComboBox` | `QComboBox` | Fluent 스타일 콤보박스 | 커스텀 view/style이 적용된 단일 선택 드롭다운. |
| `ElaContentDialog` | `QDialog` | 마스크가 있는 content dialog | 제목, 내용, 확인/취소류 버튼을 가진 모달 dialog. |
| `ElaDialog` | `QDialog` | 일반 dialog 베이스 | Ela 스타일이 적용된 기본 dialog. |
| `ElaDockWidget` | `QDockWidget` | dock widget | 커스텀 title bar와 스타일을 가진 docking 패널. |
| `ElaDoubleSpinBox` | `QDoubleSpinBox` | 실수 spin box | Fluent 스타일의 double 입력 spin box. |
| `ElaDrawerArea` | `QWidget` | drawer 표시 영역 | drawer container/header와 함께 슬라이드형 보조 패널을 구성한다. |
| `ElaDxgiManager` | `QObject` | DXGI 캡처 관리자 | Windows DXGI 기반 화면 캡처. 자동 장치 선택과 native 대비 효율 개선이 목적이다. |
| `ElaDxgiScreen` | `QWidget` | DXGI 화면 표시 위젯 | `ElaDxgiManager` 캡처 결과를 위젯에 표시하는 보조 화면 컴포넌트. |
| `ElaEvent` | `QObject` | 이벤트 데이터 객체 | `ElaEventBus`에 전달되는 이벤트 단위. |
| `ElaEventBus` | `QObject` | 이벤트 버스 | 컴포넌트 간 loose coupling 이벤트 전달용 전역/공유 버스. |
| `ElaExponentialBlur` | `QObject` | 지수 blur 처리 | 이미지/픽셀 데이터에 대한 exponential blur 유틸리티. |
| `ElaFlowLayout` | `QLayout` | flow layout | 항목을 가로/세로 공간에 따라 자동 줄바꿈 배치한다. 애니메이션을 지원한다. |
| `ElaIcon` | plain class | 아이콘 유틸리티 | `ElaIconType::IconName` 기반 아이콘 렌더링/폰트 아이콘 유틸리티. |
| `ElaIconButton` | `QPushButton` | 아이콘 버튼 | Ela icon, hover/press style, icon size 등을 가진 버튼. |
| `ElaImageCard` | `QWidget` | 이미지 카드 | 이미지 중심의 카드형 표시 위젯. |
| `ElaInteractiveCard` | `QPushButton` | 상호작용 카드 | 이미지와 텍스트가 들어간 클릭형 투명 카드. |
| `ElaKeyBinder` | `QLabel` | 단일 키 바인더 | 키 입력을 표시/저장하는 단축키 바인딩 UI. |
| `ElaLCDNumber` | `QLCDNumber` | LCD 숫자 표시 | 스타일이 적용된 숫자 표시 위젯. |
| `ElaLineEdit` | `QLineEdit` | 입력창 | Fluent 스타일 line edit. clear/search 등 확장 UI와 함께 쓰인다. |
| `ElaListView` | `QListView` | 리스트 뷰 | 커스텀 scrollbar/style이 적용된 list view. |
| `ElaLog` | `QObject` | 로그 유틸리티 | 메시지 로그 처리용 객체. |
| `ElaMenu` | `QMenu` | 메뉴 | Fluent 스타일 context/menu popup. |
| `ElaMenuBar` | `QMenuBar` | 메뉴바 | `ElaMenu`와 연동되는 스타일드 menu bar. |
| `ElaMessageBar` | `QWidget` | toast/message bar | success/warning/error/info 메시지를 여러 방향과 anchor 위치로 표시한다. |
| `ElaMessageButton` | `QPushButton` | 메시지 팝업 버튼 | 클릭 시 message bar를 띄우는 용도의 버튼 컴포넌트. |
| `ElaMultiSelectComboBox` | `QComboBox` | 다중 선택 콤보박스 | checkbox list 형태의 multi-select dropdown. |
| `ElaNavigationBar` | `QWidget` | navigation bar | `ElaWindow`에서 쓰이는 트리형/라우팅형 navigation 구성요소. |
| `ElaPivot` | `QWidget` | pivot navigation | 상단 탭/segment에 가까운 pivot형 navigation. |
| `ElaPlainTextEdit` | `QPlainTextEdit` | plain text editor | 스타일이 적용된 multi-line plain text edit. |
| `ElaPopularCard` | `QWidget` | popular card | 강조형 카드. floater와 버튼을 포함해 추천/인기 항목 표현에 쓰인다. |
| `ElaProgressBar` | `QProgressBar` | progress bar | 선형 진행률 표시. |
| `ElaProgressRing` | `QWidget` | progress ring | 원형 진행률/로딩 표시. README 목록에는 없지만 공개 헤더로 제공된다. |
| `ElaPromotionCard` | `QWidget` | promotion card | 이미지/제목/설명/버튼을 가진 프로모션 카드. |
| `ElaPromotionView` | `QWidget` | promotion card view | 여러 `ElaPromotionCard`를 배치/전환하는 프로모션 영역. |
| `ElaPushButton` | `QPushButton` | 기본 버튼 | primary/light/dark 등 Ela 스타일의 push button. |
| `ElaRadioButton` | `QRadioButton` | radio button | Fluent 스타일 단일 선택 버튼. |
| `ElaReminderCard` | `QPushButton` | reminder card | 이미지가 있는 알림/리마인더 카드. |
| `ElaRoller` | `QWidget` | 무한 roller selector | wheel/roller 방식으로 항목을 선택하는 위젯. |
| `ElaRollerPicker` | `QPushButton` | roller picker 버튼 | 버튼 클릭으로 roller 선택 컨테이너를 띄우는 picker. README 목록에는 없지만 공개 헤더로 제공된다. |
| `ElaScrollArea` | `QScrollArea` | scroll area | 커스텀 scrollbar와 마우스 드래그 스크롤 옵션을 제공한다. |
| `ElaScrollBar` | `QScrollBar` | scrollbar | Fluent 스타일 스크롤바. |
| `ElaScrollPage` | `QWidget` | scroll page | breadcrumb와 stack page 구조를 포함하는 스크롤 페이지 베이스. |
| `ElaScrollPageArea` | `QWidget` | scroll page 영역 | `ElaScrollPage` 내부 section/area를 구성하는 컨테이너. |
| `ElaSlider` | `QSlider` | slider | Fluent 스타일 value slider. |
| `ElaSpinBox` | `QSpinBox` | 정수 spin box | Fluent 스타일 integer spin box. |
| `ElaStatusBar` | `QStatusBar` | status bar | 스타일이 적용된 상태바. |
| `ElaSuggestBox` | `QWidget` | 검색/추천 입력 박스 | placeholder, case sensitivity, suggestion 추가/삭제/클릭 signal을 제공한다. |
| `ElaSuggestBox::SuggestData` | struct | 추천 항목 데이터 | icon, text, key, custom `QVariantMap` 데이터를 담는 nested public struct. |
| `ElaTabBar` | `QTabBar` | Chrome 스타일 tab bar | 탭 추가/닫기/이동 UI를 커스텀한다. |
| `ElaTableView` | `QTableView` | table view | 커스텀 scrollbar/style이 적용된 table view. |
| `ElaTabWidget` | `QTabWidget` | Chrome 스타일 tab widget | `ElaTabBar`를 사용하는 탭 페이지 컨테이너. |
| `ElaText` | `QLabel` | 텍스트 라벨 | title/body/caption 등 text style preset을 가진 라벨. |
| `ElaTheme` | `QObject` | 테마 관리자 | light/dark 모드, theme color, painter helper 등 전역 테마 관리. |
| `ElaToggleButton` | `QWidget` | 토글 버튼 | 선택/비선택 상태를 갖는 버튼형 toggle. README에는 없지만 공개 헤더로 제공된다. |
| `ElaToggleSwitch` | `QWidget` | 스위치 | on/off 스위치 UI. |
| `ElaToolBar` | `QToolBar` | toolbar | Fluent 스타일 tool bar. |
| `ElaToolButton` | `QToolButton` | dropdown tool button | `ElaMenu`와 연동 가능한 도구 버튼. |
| `ElaToolTip` | `QWidget` | tooltip | 커스텀 tooltip 표시 위젯. README에는 없지만 공개 헤더로 제공된다. |
| `ElaTreeView` | `QTreeView` | tree view | 커스텀 scrollbar/style이 적용된 tree view. |
| `ElaWidget` | `QWidget` | 무프레임 모달/일반 위젯 | Ela 스타일의 frameless widget wrapper. |
| `ElaWindow` | `QMainWindow` | navigation 포함 메인 윈도우 | 무프레임 메인 윈도우, navigation bar, central stack, app bar를 통합한다. |

## 공통 enum/타입 그룹

`ElaDef.h`는 클래스는 아니지만 대부분의 공개 클래스 API에서 함께 사용된다.

| 그룹 | 내용 |
|---|---|
| `ElaApplicationType` | window display mode. `Normal`, `ElaMica`, Windows 전용 `Mica`, `MicaAlt`, `Acrylic`, `DWMBlur` 등. |
| `ElaThemeType` | `Light`, `Dark` 및 테마 색상 enum. |
| `ElaIconType` | Font icon 이름 enum. `ElaIcon`, `ElaIconButton`, card류, suggest item에서 사용된다. |
| `ElaMessageBarType` | message bar 유형/위치/표시 방향 계열 enum. |
| `ElaNavigationType` | navigation node/page 동작, display mode, route 관련 enum. |
| 기타 | text type, button type, tab style 등 각 위젯의 속성값으로 쓰이는 enum이 포함된다. |

## DeveloperComponents 클래스

아래 클래스들은 빌드 include 경로에는 들어가지만 이름과 위치상 공개 위젯을 구성하는 내부/개발 보조 클래스에 가깝다. 직접 사용 가능하더라도 API 안정성은 `ElaWidgetTools/*.h` 공개 클래스보다 낮게 보는 것이 좋다.

### Model/View/Delegate

| 클래스 | 기반 클래스 | 역할 |
|---|---:|---|
| `ElaBaseListView` | `QListView` | 공통 list view 베이스. custom scrollbar와 view 동작을 공유한다. |
| `ElaBreadcrumbBarDelegate` | `QStyledItemDelegate` | breadcrumb 항목 렌더링 delegate. |
| `ElaBreadcrumbBarModel` | `QAbstractListModel` | breadcrumb 항목 model. |
| `ElaCalendarDelegate` | `QStyledItemDelegate` | calendar 날짜 셀 렌더링 delegate. |
| `ElaCalendarModel` | `QAbstractListModel` | calendar 날짜 데이터 model. |
| `ElaCalendarTitleDelegate` | `QStyledItemDelegate` | calendar title/month/year 영역 delegate. |
| `ElaCalendarTitleModel` | `QAbstractListModel` | calendar title 영역 model. |
| `ElaColorDisplayDelegate` | `QStyledItemDelegate` | 색상 swatch/display delegate. |
| `ElaColorDisplayModel` | `QAbstractListModel` | color dialog 색상 목록 model. |
| `ElaComboBoxView` | `QListView` | combo box popup list view. |
| `ElaFooterDelegate` | `QStyledItemDelegate` | navigation footer item delegate. |
| `ElaFooterModel` | `QAbstractListModel` | navigation footer item model. |
| `ElaNavigationModel` | `QAbstractItemModel` | navigation tree model. |
| `ElaNavigationNode` | `QObject` | navigation item/node 데이터 객체. |
| `ElaNavigationView` | `QTreeView` | navigation tree view. |
| `ElaPivotModel` | `QAbstractListModel` | pivot item model. |
| `ElaPivotView` | `QListView` | pivot item view. |
| `ElaSuggestDelegate` | `QStyledItemDelegate` | suggest item delegate. |
| `ElaSuggestModel` | `QAbstractListModel` | suggestion list model. |

### Popup/Container/Composition

| 클래스 | 기반 클래스 | 역할 |
|---|---:|---|
| `ElaCalendarPickerContainer` | `QWidget` | calendar picker popup/container. |
| `ElaCentralStackedWidget` | `QWidget` | `ElaWindow` central stack와 blur/transition 영역. |
| `ElaColorPicker` | `QWidget` | color dialog 내부 색상 picker. |
| `ElaColorPreview` | `QWidget` | color dialog 내부 preview. |
| `ElaCustomWidget` | `QDialog` | custom widget dialog 베이스. |
| `ElaCustomTabWidget` | `ElaCustomWidget` | tab 관련 custom dialog/widget. |
| `ElaDockWidgetTitleBar` | `QWidget` | dock widget 전용 title bar. |
| `ElaDrawerContainer` | `QWidget` | drawer popup/container. |
| `ElaDrawerHeader` | `QWidget` | drawer header. |
| `ElaKeyBinderContainer` | `QWidget` | key binder popup/container. |
| `ElaMaskWidget` | `QWidget` | modal/content dialog의 dim mask. |
| `ElaPopularCardFloater` | `QWidget` | popular card hover/floating action 영역. |
| `ElaRollerPickerContainer` | `QWidget` | roller picker popup/container. |
| `ElaSuggestBoxSearchViewContainer` | `QWidget` | suggest box 검색 결과 popup/container. |
| `ElaThemeAnimationWidget` | `QWidget` | theme 전환 animation overlay. |

### Style 클래스

| 클래스 | 기반 클래스 | 역할 |
|---|---:|---|
| `ElaCheckBoxStyle` | `QProxyStyle` | `ElaCheckBox` rendering/style. |
| `ElaColorValueSliderStyle` | `QProxyStyle` | color value slider style. |
| `ElaComboBoxStyle` | `QProxyStyle` | combo box rendering/style. |
| `ElaLCDNumberStyle` | `QProxyStyle` | LCD number style. |
| `ElaLineEditStyle` | `QProxyStyle` | line edit style. |
| `ElaListViewStyle` | `QProxyStyle` | list view style. |
| `ElaMenuBarStyle` | `QProxyStyle` | menu bar style. |
| `ElaMenuStyle` | `QProxyStyle` | menu popup style. |
| `ElaNavigationStyle` | `QProxyStyle` | navigation item painting/animation style. |
| `ElaPivotStyle` | `QProxyStyle` | pivot item style. |
| `ElaPlainTextEditStyle` | `QProxyStyle` | plain text edit style. |
| `ElaProgressBarStyle` | `QProxyStyle` | progress bar style. |
| `ElaRadioButtonStyle` | `QProxyStyle` | radio button style. |
| `ElaScrollBarStyle` | `QProxyStyle` | scrollbar style. |
| `ElaSliderStyle` | `QProxyStyle` | slider style. |
| `ElaSpinBoxStyle` | `QProxyStyle` | spin box style. |
| `ElaStatusBarStyle` | `QProxyStyle` | status bar style. |
| `ElaTabBarStyle` | `QProxyStyle` | tab bar style. |
| `ElaTableViewStyle` | `QProxyStyle` | table view style. |
| `ElaToolBarStyle` | `QProxyStyle` | toolbar style. |
| `ElaToolButtonStyle` | `QProxyStyle` | tool button style. |
| `ElaTreeViewStyle` | `QProxyStyle` | tree view style. |
| `ElaWindowStyle` | `QProxyStyle` | window/global style. |

### Platform/Utility

| 클래스 | 기반 클래스 | 역할 |
|---|---:|---|
| `ElaDxgi` | `QObject` | DXGI 캡처 low-level helper. Windows 전용 성격이 강하다. |
| `ElaIntValidator` | `QIntValidator` | Ela 입력 컴포넌트용 integer validator. |
| `ElaMicaBaseInitObject` | `QObject` | Mica/window backdrop 초기화 보조 객체. |
| `ElaWinShadowHelper` | `QObject` | Windows shadow/border helper. |

### Command

| 클래스 | 기반 클래스 | 역할 |
|---|---:|---|
| `ElaNavigationRouteCommand` | `ElaActionCommand` | navigation route 변경 command. |
| `ElaScrollPageRouteCommand` | `ElaActionCommand` | scroll page route 변경 command. |
| `ElaWindowStackChangeCommand` | `ElaActionCommand` | `ElaWindow` central stack 변경 command. |

## 사용 우선순위

1. 화면을 빠르게 구성할 때는 `ElaWindow`, `ElaApplication`, `ElaTheme`, `ElaNavigationBar`, `ElaScrollPage`를 먼저 본다.
2. 일반 Qt widget 대체가 필요하면 `ElaPushButton`, `ElaLineEdit`, `ElaComboBox`, `ElaCheckBox`, `ElaRadioButton`, `ElaTableView`, `ElaTreeView`, `ElaListView`를 사용한다.
3. 카드/대시보드 UI에는 `ElaPromotionCard`, `ElaPromotionView`, `ElaPopularCard`, `ElaReminderCard`, `ElaImageCard`, `ElaInteractiveCard`, `ElaAcrylicUrlCard`가 적합하다.
4. 팝업성 UI는 `ElaContentDialog`, `ElaColorDialog`, `ElaMessageBar`, `ElaCalendarPicker`, `ElaRollerPicker`, `ElaSuggestBox`를 우선 검토한다.
5. `DeveloperComponents`는 내부 구현 확장, 스타일 커스터마이징, 문제 추적 시에만 직접 참조하는 것을 권장한다.
